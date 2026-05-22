# Saleae Logic Captures

These are from several capture sessions.

### Aperture Control

For iris captures, labelled using the `f4.0-f5.6.sal` style scheme as attempts to capture a full command and lens iris change:

- The camera was mostly manual, had depth-of-field preview enabled
- The camera was set to the first f-stop value in the file-name
- I changed the focus control ring one click, which results in the second f-stop in the file name
- Logic2 was configured to trim the capture around the channel4 falling edge which occus when the iris changes

> Ch4 edge duration increases as the iris change takes longer. Unsure if this is some kind of 'ready' signal or part of the autoexposure behaviour?

Additional iris captures using the scheme demonstrate larger changes, i.e. `f2.8-f16.sal`.
Also captured a reversed version of the above process, starting with depth-of-field preview enabled at a smaller f-stop, and then disabling it to open up. i.e. `f8.0-f2.8.sal`.

A pair of *dof-preview enabled* longer runs from one end to the other are included in `iris-sweep-f2.8-to-f32.sal` and `iris-sweep-f32-to-f2.8.sal`. These generally seem to have corresponding negative pulses on CH4 when the iris changes physically. 

For just the command ring *without dof preview* enabled there is no triggerable edge. A single capture `iris-ring-sweep-f2.8-to-f32.sal` starts at f2.8, and I increment the ring gradually until f32. A reversed version `iris-ring-sweep-f32-to-f2.8.sal` is also provided.



### Focus Control

When the camera is in autofocus mode, there is no visible change to the camera or lens when the focus ring is rotated. These captures are `focus-ring-...`, with varying distance and speeds, in both directions.

When the camera is in manual focus mode, moving the focus control ring causes motor acutuation. The logs following `focus-ring-af-*` are in that mode and have motor actuation signals on CH2.





### Notes

Other captures are from a prior session and are annotated where relevant.