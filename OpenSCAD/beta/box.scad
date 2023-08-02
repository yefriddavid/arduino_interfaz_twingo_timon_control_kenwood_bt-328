

$fn = 100; // resolution

clearance=0.25; //clearances for 3D printing to make parts easily fit where needed
// width = 38.6+3; //width of the case(X)
// width = 68.6+3; //width of the case(X)
width = 40.6+3;


//depth = 53.3+3; //depth of the case (Y)
depth = 105; //depth of the case (Y)
depthSpace = 5; //little space on both sides of the case to store loose wires and make it easier to fit components
height = 22; //height of the case (Z)
//height = 25;
indentHeight = 2; // tells us how far the cover overlaps the case
wallWidth = 3; // wall width

//union()
//    {
difference(){
    difference() {
        //build a box
   
        // cut a working area space
        difference() {
        //build a box
            color([.5,.5,.5]) linear_extrude(height, convexity = 10) {
                offset(r = wallWidth)
                square([width, depth + (2 * depthSpace)], true);
            };

            // cut a working area space
            translate([0, 0, wallWidth]) linear_extrude(height,         convexity = 10) square([width, depth], true);
        }
        // cut a space on the sides of the working area
        // can be used to hold an excess wires
        for (i = [-1, 1])
          translate([0, i * (depth / 2 + depthSpace / 2),   wallWidth]) linear_extrude(height, convexity = 10) square([width - 2 * depthSpace, depthSpace], true);
        
        
        for (i = [
            [-1, 1],
            [1, -1],
            [-1, -1],
            [1, 1]
        ])
      translate([i[0] * (width / 2 - depthSpace / 2), i[1] * (depth / 2 + depthSpace / 2), height - 4 / 5 * height]) linear_extrude(4 / 5 * height, convexity = 10) circle(d = 2.5);
    }
    translate([0, 0, height - indentHeight])
    linear_extrude(indentHeight, convexity = 10) 
    difference() {
      offset(r = wallWidth) 
        square([width, depth + 2 * depthSpace], center = true);
        square([width + wallWidth, depth + 2 * depthSpace + wallWidth], center = true);
    }
    
    
    
    
    // ranuras de salida
        squareXHole = [
        [
          [ -wallWidth, 31.7, wallWidth + 1 ],
          [ wallWidth + 0.001, 11.43 + 2, 10.8 + 2 + 50 ]
        ], // usb port
        [
          //[ -wallWidth, 3.3, wallWidth + 3 ],
          //[ wallWidth + 0.001, 8.9 + 2, 10.8 + 2 + 50 ]
        ] // power plug
        ];
    //width,height add 0.001 to remove OpenSCAD's zero-width wall-when-difference same width artifact
    for (i = squareXHole)
        color("red") translate(i[0]) cube(i[1]);
    
    }



        /*pcbScrewPositions = [
            [ 15.97, 16.54, wallWidth ],
            [ -15.97, 16.54, wallWidth ],

            [ 15.97, -20.54, wallWidth ],
            [ -15.97, -20.54, wallWidth ],

           // [ -15.24, -50.8, wallWidth ],
            //[ -66.2, -35.56, wallWidth ],
            //[ -66.2, -7.62, wallWidth ]
        ];
        // add screw hole insets
        for (i = pcbScrewPositions) {
            translate([ i[0], i[1], i[2] ]) cylinder(h = 2.5, r1 = 5.5 / 2, r2 = 4.5 / 2);
            translate([ i[0], i[1], i[2] + 2.5 ]) cylinder(h = 3, r = 1.2);
        }
    }*/
    
    
module dovetail(max_width = 5, min_width = 3, depth = 5, height = 20) {
  linear_extrude(height = height , convexity = 2) polygon(paths = [
    [0, 1, 2, 3, 0]
  ], points = [
    [-min_width / 2, 0],
    [-max_width / 2, depth],
    [max_width / 2, depth],
    [min_width / 2, 0]
  ]);
  echo("angle: ", atan((max_width/2-min_width/2)/depth));
}
//dovetail();














