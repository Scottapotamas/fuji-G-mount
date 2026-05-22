# GF Protocol Notes

Sniffing of the communications between the body and lens is achieved with a modified MCEX-45G, and builds from the basic electrical analysis described in [the electrical README](/electrical).

### Logic Analyser Captures

Useful trace files are committed to the `captures` folder.

These files require Saleae's Logic 2 tool for viewing. It's freely available for download on their website [here](https://www.saleae.com/downloads/).

Specific packets or sections of interest are converted into a more digestible form and are saved in `/packet-captures` as hex encoded binary files.



# SPI Communication

We can make the assumption about the specific IN/OUT pins because there ares in the logic captures which show one-way initial send packets, and occasional one-way responses.

![controller-peripheral-evidence](./images/controller-peripheral-evidence.png)

Based on this, we can assume that:

- Pin 9 is body's DATA OUT line.
- Pin 10 is a 1.5MHz SPI-style clock signal.
- Pin 11 is the body's DATA IN line.

With this in mind, we now aim to identify the properties of the communications bus and determine if it's typical SPI or some Fuji special sauce.

- A transaction consists of 32-bits at minimum
  - Almost all transactions are 32-bits long.
  - During startup, a pair of 1048-bit long transactions occur with a 3ms gap - these are the longest identified transactions.
  - As the division of  `1048` and the potential bits-per-transfer should be an integer, we can reasonably throw out `16` and `32` bit transfer sizes.

By manually inspecting logic captures, one example section helps determine the clock behaviour.

- The clock is high when inactive (CPOL = 1).
- Data is valid on the clock's trailing edge (CPHA = 1)
  - Demonstrated by the edges on the first falling edge, and on falling edges aligned to 8-bit sequences.
    ![clock-phase-evidence](./images/clock-phase-evidence.png)

As with typical SPI busses working with bidirectional transfers, there a fairly visible 1-packet delay between the body writing a field and the lens response. When I'm listing tx/rx pairs in a given transaction in this document, that offset isn't included unless specified.

# Protocol Analysis



## Packet Structure

The last byte appears to be a checksum

## Checksum







# Packet Analysis



## 'Idle' Packets

When the camera is powered on but is otherwise sitting idle, we see a burst of transactions occur every 40ms. These might not actually be idle, but they don't appear to change with iris control ring, current iris value, or focus ring movement.

These packets represent the bulk of 'noise' when watching packet traces, so understanding, decoding and then filtering them represents a worthwhile effort.

![idle-burst-4](./images/idle-burst-4.png)

| Transmission # | Camera                | Lens                  |
| -------------- | --------------------- | --------------------- |
| 1              | `0x00 0x00 0x08 0x20` | -                     |
| 2              | `0x?? 0x10 0x80 0x??` | `0x08 0x00 0x88 0x32` |
| 3              | -                     | `0x03 0x80 0x08 0x3C` |
| 4              | `0x08 0x00 0x88 0x??` | `0x?? 0x00 0x80 0x??` |

On every third burst, we have 2 additional transactions for a 6 transaction 'group'.

![idle-burst-6](./images/idle-burst-6.png)

| Transmission # | Camera                | Lens                  |
| -------------- | --------------------- | --------------------- |
| 1              | `0x00 0x00 0x08 0x20` | -                     |
| 2              | `0x?? 0x10 0x80 0x??` | `0x08 0x00 0x88 0x32` |
| 3              | `0x00 0x00 0x09 0xA6` | `0x03 0x80 0x08 0x3C` |
| 4              | `0x?? 0x00 0x88 0x??` | `0x?? 0x00 0x89 0x??` |
| 5              | -                     | `0x00 0x15 0x09 0x9A` |
| 6              | `0x08 0x00 0x89 0xB8` | `0x?? 0x00 0x80 0x??` |

For both the 4 and 6 packet bursts, the first bytes marked as `0x??` seem to vary between subsequent bursts, but a random sampling of 5 bursts in a row gives a feel that they're not immediately exhibiting packet counting behaviour.

The final bytes marked `0x??` are most likely a CRC, but it's not clear yet.


## Identification Packets

After the camera is powered on, a series of `131B` transactions occur (each sent twice 3ms apart). Both transmissions appear to have identical payloads.

### GF45mm

The first transaction starts the first two bytes with `0x00 0x00`, and ends with `0xAF`.

The second transaction starts with `0xFF 0xFF` and ends with `0xAD`.

The payload (in hex) is:

```
4c52 3130 3641 0000 4653 534e 5730 3036
4746 3435 6d6d 4632 2e38 2052 2057 5200
0000 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
3234 3033 3338 3636 3035 0156 0100 0100
0100 0100 c801 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
```

These transactions are from the lens to the body and **describe the lens**. 

- The first section of data is ASCII: `LR106A  FSSNW006GF45mmF2.8 R WR` 
  - Not sure what the first half means yet.
  - The last half is obvious obvious, the lens is officially labelled as  `GF45mmF2.8 R WR`.
- The second block of data in the payload is `2403386605 V` `È` in ASCII, which isn't immediately obvious
  - TODO work out what this data means?

### GF110mm

The first transaction starts the first two bytes with `0x00 0x00`, and ends with `0x0B`.

The second transaction starts with `0xFF 0xFF` and ends with `0x09`.

The payload (in hex) is:

```
4c52 3130 3441 0000 4653 534e 5731 3034
4746 3131 306d 6d46 3220 5220 4c4d 2057
5200 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
3035 4330 3030 3234 0000 0160 0110 0110
0110 0110 c801 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
```

These transactions are from the lens to the body and **describe the lens**. 

- The first section of data is ASCII: `LR104A  FSSNW104GF110mmF2 R LM WR`
  - Not sure what the first half means yet.
  - The last half is obvious, the lens is officially labelled as `GF110mmF2 R LM WR`.
- The second block of data in the payload is `05C00024` `È` in ASCII
  - TODO work out what this data means

### GFX50R

> These body identification packets occur somewhat later than the lens identification packets, and only when the `GF110mm` is mounted.

The first transaction starts the first two bytes with `0x00 0x00`, and ends with `0x19`.

The second transaction starts with `0xFF 0xFF` and ends with `0x17`.

The payload (in hex) is:

```
5350 5833 0000 0000 0000 4746 5820 3530
5200 0000 0000 0000 0000 0000 0000 4746
5820 3530 5200 0000 0000 0000 0035 3933
3533 3433 3833 3633 3131 3831 3131 3339
3744 3031 3031 3130 3834 3102 2001 3501
0001 0001 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
0000 0000 0000 0000 0000 0000 0000 0000
```

These transactions are from the body to the lens and **describe the body.** 

- The first section of data is ASCII: `SPX3` `GFX 50R` `GFX 50R` (whitespace trimmed)
  - Unsure of what `SPX3` represents.
  - The repeated pair of `GFX 50R` string sequences match the body under test.
- The second section of data is unknown.
  - `59353438363118111397D010110841   5` in ASCII, with some unprintable bytes
  - Unknown data





## Iris Packets

- What happens when the iris ring is rotated
- What happens when the camera wants to close the iris for exposure or photos

Starts when a packet we don't recognise prior to iris event `LOW` is found (manually).

The iris event was 275ms long.

Preceded by a standard set of IDLE 6-burst transmissions (coincidence or intentional?).

#### Packet 1 

Camera: `0x12 0x40 0x18 0xBA`

Lens: -

#### Packet 2

Camera: `0x09 0x10 0x80 0x2A`

Lens: `0x08 0x00 0x98 0xB6`

#### Packet 3

Camera:  `0x00 0x00 0x3F 0xC6` 

Lens: `0x12 0x40 0x18 0xBA`

##### Packet 4

Camera: `0x0A 0x00 0x98 0x86`

Lens: `0x09 0x00 0xBF 0xE0`

Iris line goes low

##### Packet 5

Camera:  `0x00 0x00 0x00 0x00`

Lens:  `0x00 0x00 0x3F 0xC6`

##### Packet 6

Camera:  `0x08 0x00 0xBF 0xD8`

Lens:  `0x0A 0x00 0x80 0x22`

##### Waiting

40ms gap starts, followed by idle packets at normal interval

`IDLE4` ` IDLE4` `IDLE6` `IDLE4` ` IDLE4` `IDLE6` 

Then iris line returns to `HIGH`.

## Iris Close Command

From the larger/recent dump of iris closures, the packet `00 00 3f c6` is found just before the iris closes in all cases. There's always another packet which has the lens responding, `n 00 bf ??` i.e. `0B 00 BF F0` immediately before the falling edge on the iris status IO.

This behaviour doesn't occur when the control ring is rotated without dof preview on.

It's unclear right now if that's a body/lens synchronisation or “prepare/execute stop-down” command.

I also noticed that the iris IO line negative pulse that occurs when stopping down/up takes an increasing amount of time based on the 'stop distance' in the transition. I suspect this signal might indicate 'iris OK' or similar. 



## Aperture Control Ring

From the large set of lens iris change captures, a pattern across the captures started to be more obvious in the packets sent from the lens to the body (i.e. body rx):

```
rx 00 02 0c ??
rx 00 03 0c ??
rx 00 04 0c ??
...
rx 00 10 0c ??
...
rx 00 16 0c ??
```

The body sends `00 00 00 00` during these packets, which probably implies the body reads a 'data ready' field from the lens?

Maybe something like this (low confidence)?

```
tx 00 00 0c ??       body asks for ring/aperture-index state
rx 00 XX 0c ??       lens reports ring/aperture ordinal or changed-position value
tx/rx n 00 8c ??     tagged transport/status wrapper for that exchange
rx n 00 80 ??        final status/result acknowledgement
```

If I encoded a hypothetical index to each accessible f-stop position on the control ring (and retrospectively 1-index it):

```
01 = f/2.8
02 = f/3.2
03 = f/3.6
04 = f/4
05 = f/4.5
06 = f/5
07 = f/5.6
08 = f/6.4
09 = f/7.1
0a = f/8
0b = f/9
0c = f/10
0d = f/11
0e = f/13
0f = f/14
10 = f/16
11 = f/18
12 = f/20
13 = f/22
14 = f/26
15 = f/29
16 = f/32
```

This seems to be validated with actual sniffed f-stop tests:

```
f2.8 -> f3.2   rx 00 02 0c 32
f3.2 -> f3.6   rx 00 03 0c 12
f3.6 -> f4.0   rx 00 04 0c 34
...
f29 -> f32     rx 00 16 0c 06
```

> This raises the question about the range of accessible f-stops on the control dial for faster/slower lenses
>
> Surely there are lenses in the GF ecosystem with more/fewer configurable apertures?

![iris-ring-sweeps-combined](images/iris-ring-sweeps-combined.png)



Now there's a known packet behaviour `00 XX 0c YY`, poking at the relationship to the CRC byte is possibly an option?

Sorting/filtering the packets out,

```
XX=02 -> YY=32
XX=03 -> YY=12
XX=04 -> YY=34
XX=05 -> YY=14
...
XX=16 -> YY=06

if XX is odd:
    YY = (XX + 0x0f) & 0x3f
else:
    YY = (XX + 0x30) & 0x3f
```

This might be reaching though.

Things to test next:

- If the control ring value is sent frequently or on event
- Does the `A` and `C` setting on the ring correspond to additional values or some other packet?
- How it behaves with shutter/half-press behaviour (sent each time or cached?)
- How fast movements are streamed out

## Focus Control Ring

The focus ring is also fly-by-wire. Because the ring isn't marked and is free to rotate infinitely, there's no easy way to capture known step values.

So a handful of captures were done to cover a range of possible packet scenarios in both manual focus mode (lens motor activates on turn), and autofocus mode where the ring isn't typically used.

- Captures with small, longer, and >revolution movements made continuously in each direction
- Captured back and forth movements, expecting to see a rough sine/triangle position trace 

After looking through the captures for unique/different packets, a packet from the lens seems to be a viable candidate for a big-endian 16-bit value:

```
rx 00 01 0c 92    +1
rx 00 04 0c b6    +4
rx 00 08 0c ba    +8

rx ff ff 0c 8c    -1
rx ff fb 0c 88    -5
rx ff f8 0c a6    -8
```

Clockwise captures are positive values, counterclockwise are negative. They seem to be relative values, not absolute position as they were larger in the 'fast' captures, and aren't published/polled at a different rate.

The body seems to queries the value with `00 00 0c b2`, and the lens responds two transactions later.

```
tx 00 00 0c b2       body asks for ring-motion state
...
tx 00 00 00 00
rx ss ss 0c cc       lens reports signed relative value
```

In the captures where the manual focus mode was active and the motor would move, we see additional `0x15` packets which I'll look into/document in their own section.

Extracting the values with timestamps and then plotting them and a running sum, gives convincing results.

![focus-ring-ccw-continuous-turns](images/focus-ring-ccw-continuous-turns.png)![focus-ring-af-cw-ccw-alternating-medium](images/focus-ring-af-cw-ccw-alternating-medium.png)
