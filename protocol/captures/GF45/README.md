# Saleae Logic Captures

These are from several capture sessions with GF45mm f2.8 and GFX50R using extension tube for sniffing.

### Aperture Control

The GF45mm F2.8 control ring has third-stop increments from f2.8 to f32.

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



## Focus Motor

A series of captures made in manual focus mode manually moving the ring small increments to cover the focus range, `focus-throw-small-spaced-moves-from-inf-to-min.sal` and a min-to-inf capture.

`focus-throw-large-alternating.sal` is a larger movement back and forth in the approx middle of the range.

Autofocus drive behaviour is in a series of captures following the scheme `focus-af-targetx-runY.sal` where X is a unique focus target that we start at and successfully focus on, and Y is the n-th repetition of the test. This is because the AF search sometimes hunts differently.

- `A` runs are on the 'long' end of the focus scale, between 10m and inf but the macro adapter is in-use so these distances aren't useful.
- `B` runs are in the approx end of the focus scale, also with the macro adapter.
- The two runs named `focus-af-targetB-slow-run` 1 and 2, there was nearly no light on the target so the autofocus had to hunt much slower to achieve a lock.

These tests were all done at wide-open f2.8 to try and keep iris change behaviour out of it.

# Power On/Off

A series of new captures `power-onX.sal` and `power-offX.sal`. Done with lens set to "2.8" Camera was in AFS setting.

The camera runs a sensor clean on shutdown.

## Preview Mode

`preview-mode-enter` and `preview-mode-exit` are variations where the lens is audibly woken up/slept but not a full camera power cycle, no sensor cleaning.

Camera was set to F2.8, 1/125, ISO1600, MF and was awake/viewfinder before going into image review.

## Sleep

Camera was in viewfinder state and allowed to disable/sleep the display. I woke it by rotating the manual focus ring. 
Set to 15-seconds.

`display-sleep` and `display-wake`.

## Lens Removal

`lens-dismount` and `lens-mount` were done while the camera was on, as a variation.

## Firmware Update

Power-up while holding DISP/BACK button brings up the update menu. `power-into-fwupdate.sal`

Display reports "Body version 3.11" and "Lens version 1.00".

# State Changes

Camera otherwise idle while changing the 3-position focus mode lever.

`mode-afc-to-afs`, `mode-afs-to-afc` and `mode-afc-to-mf` and `mode-mf-to-afc` are the possible individual directions.

`mode-afs-afc-mf-sweep` sweeps through them and back.

# Half-shutter

The lens was set to f4. Shutterspeed at 1/125. Iso 1600. 

- `half-shutter-mf-lenscap` for manual focus mode with lenscap
- `half-shutter-mf` for manual focus mode, no lenscap
- `half-shutter-afs-lenscap` includes focus attempt
- `half-shutter-afs` includes focus attempt

### Notes

`idle-13sec.sal` is captured with the same channel config as the iris/focus captures. The camera was configured in AF mode, lens was on F2. Screen was on, no user interaction before/during the capture.


Other captures are from a prior session and are annotated where relevant.