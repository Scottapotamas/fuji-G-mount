# Fujifilm G Mount
The Fujifilm G Mount is used by the Fujifilm GFX line of digital medium format mirrorless cameras.

Since the announcement in 2016, the GF lens ecosystem has been gaining popularity due to the superb optical performance, high megapixel camera bodies (GFX100), and low cost (well... compared to other MFD systems).

One minor challenge compared to most existing lens ecosystems - **all GF lenses are fly-by-wire**. Sensing user interaction with the aperture or focus rings, and commanding the iris and focus mechanisms will require computer control. Additionally, lenses such as the 110mm f2 and 250mm f4 have floating optical elements which require power/control from the body in order to become optically valid.

____

My long-term photography/hobby goals are rather ambitious; *build a film camera from scratch using modern lenses*. A 120 'body' for my GF lenses feels like the right kind of wrong...

## Aims

- Document the mechanics of the G Mount sufficiently to create native-compatible mounts from scratch.
- Reverse-engineer & document the communications between the lens and body:
  - Pinout for the electrical contacts in the lens mount,
  - Power supply requirements for lenses,
  - Sniff the communications between the lens and camera, and document any specifics if possible.
- Write a library capable of parsing lens data (in both directions) in real-time.
- Create an interface PCB which pretends to be a GFX camera - powers and controls an attached lens, can read lens info and focus/iris ring feedback.

## Prior Art?

At time of writing, no publicly available information about the mount's mechanics could be found other than the flange distance and internal diameter.

Similarly, any electrical interface or protocol information is not in the public domain.

Several active (3rd party) lens adaptors *are* on the market, allowing smart control over Canon EF, Contax C645, and others. Therefore we can guess at least three different groups have successful implementations with varying levels of functionality.

## What's the plan

1. Buy a genuine Fujifilm extension tube [MCEX-45G WR](https://fujifilm-x.com/global/products/accessories/mcex-45g-wr/) to act as a ground-truth mechanical mount.
   - The absurd $500AUD pricepoint is painful, but won't risk my camera or lenses. I managed to get 25% off MSRP.
   - I could use one of the $150AUD Viltrox clone extension tubes later on, but I want an accurate first-party reference to build against.

2. Create detailed 3D models of the male and female mount geometries, identify screws/springs/gaskets used.

3. Dissemble the extension tube, design a replacement 'cylinder' to mount the genuine mounting faces onto. Or just seal it's fate and drill a hole in the adaptor...
   - Expose the lens and body electrical contacts through a loom or connector - ideally each side can be separated at will for easier debugging
4. Map the electrical connections between the body and lens, create rough specs for power rails, determine the style of communication and electrical implementation(s) in use.

5. Assuming no strange electrical interfaces are used, connect the logic analyser/scope and build out a corpus of messages sent between the lens and body.

## What have we learnt

Nothing yet.