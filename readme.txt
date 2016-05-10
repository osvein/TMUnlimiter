TMUnlimiter by arc_

Intro
-----
This little tool will patch TrackMania Nations/United Forever in-memory, removing
(almost) all block placement limitations in its track editor. More specifically it
allows you to:
* Place overlapping blocks
* Place ground-only objects in the air, and air-only (or underground-only) objects
  on the ground.
* Oversize tracks: enlarge the track area size up to a maximum of 256x256! (see further below)

The tool was made for version 2.11.26, though it's written to keep working for
at least a few upcoming versions.

Installation
------------
Simply extract the archive to your TMUF/TMNF directory and start the .exe.
It will launch the game, patch it in-memory (it doesn't touch any files on the
harddisk), and quit, leaving the patched game running.

To uninstall, simply remove the files again. TMUnlimiter does not create, alter
or delete any files, and does not write anything to the registry.

Oversize tracks
---------------
TMUnlimiter allows you to customize the track area size and enlarge it up to 256x256 units
(up from e.g. the default 32x32 for Stadium). To do this, you simply edit TMUnlimiter.ini
and enter the desired size in the format x,y,z (x = width, y = height, z = depth). This
custom size will then be applied to any new tracks you create. After you have created
and saved your track, you can revert the size setting to the default - the size of
your track will stay stored in the .gbx.

IMPORTANT: for *playing* tracks that are larger than usual, you *also* need TMUnlimiter.
Even though the track size is stored in the .gbx, TrackMania overrides this information
with the default track size for the chosen environment. Therefore, if you enlarge your track
and place blocks outside of the default area, TrackMania will not load these blocks or just crash.
TMUnlimiter disables this overriding behaviour so that the track size stored in the .gbx
is retained, both for editing and playing the track.

For regular blockmixing (e.g. placing overlapping blocks) however, you only need to
run TMUnlimiter while creating the map; playing can be done without it.


Disclaimer
----------
I am not responsible for any damage this program might cause to your computer,
or for lost work because of a crash. Use this program at your own risk.


Updates
-------
More information and updates can be found at the official forum thread:
  http://forum.mania-creative.com/thread-2421.html
