# Saleae Logic Captures

These are from one capture session with GF110mm F2 and GFX50R using extension tube for sniffing.

### Aperture Control

The GF110mm F2 control ring has third-stop increments from f2 to f22.

For iris captures, labelled using the `f4.0-f5.6.sal` style scheme as attempts to capture a full command and lens iris change:

- The camera was mostly manual, had depth-of-field preview enabled
- The camera was set to the first f-stop value in the file-name
- I changed the focus control ring one click, which results in the second f-stop in the file name
- Logic2 was configured to trim the capture around the channel4 falling edge which occus when the iris changes

> Ch4 edge duration increases as the iris change takes longer. Unsure if this is some kind of 'ready' signal or part of the autoexposure behaviour?

Additional iris captures using the scheme demonstrate larger changes, i.e. `f2.8-f16.sal`.
Also captured a reversed version of the above process, starting with depth-of-field preview enabled at a smaller f-stop, and then disabling it to open up. i.e. `f8.0-f2.8.sal`.

A pair of *dof-preview enabled* longer runs from one end to the other are included in `iris-sweep-f2.0-to-f22.sal` and `iris-sweep-f22-to-f2.0.sal`. These generally seem to have corresponding negative pulses on CH4 when the iris changes physically. 

For just the command ring *without dof preview* enabled there is no triggerable edge. A single capture `iris-ring-sweep-f2.0-to-f22.sal` starts at f2.0, and I increment the ring gradually until f22. A reversed version `iris-ring-sweep-f22-to-f2.0.sal` is also provided.

> It was a little unclear in some tests if the camera was changing iris value immediately after a ring rotation, sometimes it would wait and I think the viewfinder brightness adjustment was easing between steps?

### Focus Control

When the camera is in autofocus mode, there is no visible change to the camera or lens when the focus ring is rotated. These captures are `focus-ring-...`, with varying distance and speeds, in both directions.

When the camera is in manual focus mode, moving the focus control ring causes motor acutuation. The logs following `focus-ring-af-*` are in that mode and have motor actuation signals on CH2.

## Focus Motor

A series of captures made in manual focus mode manually moving the ring small increments to cover the focus range, `focus-throw-from-min-to-half.sal` is small increments roughly one second apart from inf (~1m on digital scale, to 2m on scale). There's faster/continuous moves from min-to-inf and inf-to-min capture.

The `focus-ring-af-` captures also include motor drive.

Autofocus drive behaviour is in a series of captures following the scheme `focus-af-targetx-runY.sal` where X is a unique focus target that we start at and successfully focus on, and Y is the n-th repetition of the test. This is because the AF search sometimes hunts differently.

- `A` runs are on the 'longer' end of the focus scale, ~3.4m indicated, but the macro adapter is in-use so these distances aren't useful, actual target was about 30cm away. Iris was set to f3.2?
- `B` runs are in the near end of the focus scale, ~1m indicated, also with the macro adapter.
- The two runs named `focus-af-targetB-runX-dark` 1 and 2, there was less light on the target and it was done at f22 which caused it to hunt a bit more.
