# GF Mount Electrical Notes

# Basics

The electrical connections between the body and lens are made with 12 spring loaded contacts (body) which mechanically align with 11 contact rectangles (lens).

## Body Side

- Spring-loaded pins are on the body side, flat pads are on the lens side.
- The spring section of the pins have a 1.0 mm diameter, and a maximum achievable travel of 0.8mm.
- The spring pins have a conical/round tip.
- The pins are gold.
- The pins are spaced 6° apart, for a total span/range of 66°. There is no pin on the vertical from the mount center-point, the outermost edge pins are aligned at +33° and -33° from the vertical datum.
- The mount (metal ring/bayonet assembly) is electrically common with the exposed metal inside the battery compartment, and `Pin 5` and `Pin 6`.

## Lens Side

- The lens-side contacts are 1.6 x 1.3 mm rectangular pads, with the long edge aligned tangentially to the circular mount.

- When looking at the back of the lens mount, the right-most pin is a 1.3 mm x 1.3 mm square contact.

- For ease of convention, I'll label this square pad as `Pin 1`, though I don't know what the official Fuji nomenclature is.

- Based on this numbering scheme, `Pin 5` and `Pin 6` are mechanically the same contact rectangle, and therefore electrically common.

- Unlike the body side mount, the lens mount/bayonet is not electrically common with `Pin 5` and `Pin 6`.

  

# Experiments with the MCEX-45G

Extension tube provides probable contacts for both sides of the mount.

- The extension tube's electrical connections are a straight 1:1 passthrough,

- therefore, the camera cannot distinguish if the tube is attached.

- Electrical connections appear to be direct connections - measurements below have measurement error.

  | Pin-Pin           | Resistance (R) |
  | ----------------- | -------------- |
  | Flange            | 0.14           |
  | 1 (square)        | 0.32           |
  | 2                 | 0.08           |
  | 3                 | 0.13           |
  | 4                 | 0.12           |
  | 5 (joined with 6) | 0.05           |
  | 6 (joined with 5) | 0.08           |
  | 7                 | 0.23           |
  | 8                 | 0.20           |
  | 9                 | 0.25           |
  | 10                | 0.28           |
  | 11                | 0.27           |
  | 12                | 0.29           |

After pulling the extension tube apart, the connections are made with a flex PCB, and substantially thicker traces are used on Pins 2 through 6 (which matches the lower resistance measurements made earlier).



# Poking around

## Test Description

Voltage measurements taken with Keithley 2701 (front panel, 2 wire setup).

Scope set to rising/falling trigger at 100mV, 1V/div and 5ms/div.

Each pin was tested with the camera off, then turned on, autofocus engaged, turned off.

The ground was assumed to be Pin 5 based on:

- Higher current traces in MCEX-45G.
- Common with Pin 6 on lens mount side.
- Electrically common (v.low resistance to Pin 6 and GFX body-side mount).

## No lens connected

GFX 50R with MCEX-45G. No lens mounted.

| Pin  | Voltage  | Scope/Notes                                                  |
| ---- | -------- | ------------------------------------------------------------ |
| 1    | 3.3V     | Goes high when camera turned on, slow fall when camera turned off. |
| 2    | ~10mV    | -                                                            |
| 3    | ~10mV    | -                                                            |
| 4    | ~0.003mV | -                                                            |
| 5    | -        | Used as ground connection.                                   |
| 6    | 0mV      | Electrically common to Pin 5.                                |
| 7    | 8mV      | -                                                            |
| 8    | 8mV      | -                                                            |
| 9    | 8mV      | -                                                            |
| 10   | 7mV      | -                                                            |
| 11   | 8mV      | -                                                            |
| 12   | 15mV     | -                                                            |

## GF45mm connected

GFX 50R with GF 45mm 2.8 via MCEX-45G.

| Pin  | Voltage              | Scope/Notes                                                  |
| ---- | -------------------- | ------------------------------------------------------------ |
| 1    | 0V                   | Never triggers scope, even with varied settings.<br />Acting as (part of ) lens detect? |
| 2    | 5.32V                | Just DC.                                                     |
| 3    | 6.72V                | Just DC.                                                     |
| 4    | 8.01V                | Just DC.<br />Minor ~100mV ripple when focus motor engages.  |
| 5    | -                    | Used as ground connection for scope                          |
| 6    | -                    | Electrically common to Pin 5                                 |
| 7    | 3.4V                 | Slow infrequent squarewaves.                                 |
| 8    | 3.38V                | High speed edges, infrequently triggered.                    |
| 9    | 0V - Normally low    | Squarewave, unclear but probably data line.                  |
| 10   | 3.3V - Normally high | Squarewave, Obviously a clock line at 1.5MHz.<br />Used periodically. |
| 11   | 0V - Normally low    | Squarewave, Obvious data line.                               |
| 12   | 3.3V - Normally high | Squarewave, no discernable pattern.<br />Seems to go low when iris closes. |