translate([0,0,0]) color("red") linear_extrude(height = 1, center = true, convexity = 10)
   import (file = "/home/schef/github/isometric-instrument/linstrument.dxf", layer = "rezi_van");

translate([0,0,1*$t]) linear_extrude(height = 3, center = true, convexity = 10)
   import (file = "/home/schef/github/isometric-instrument/linstrument.dxf", layer = "vod_3.5");