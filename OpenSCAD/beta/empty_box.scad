$fn = 100; // resolution

clearance=0.25; //clearances for 3D printing to make parts easily fit where needed
// width = 38.6+3; //width of the case(X)
width = 68.6+3; //width of the case(X)

//depth = 53.3+3; //depth of the case (Y)
depth = 53.3+3; //depth of the case (Y)
depthSpace = 5; //little space on both sides of the case to store loose wires and make it easier to fit components
height = 35; //height of the case (Z)
//height = 25;
indentHeight = 2; // tells us how far the cover overlaps the case
wallWidth = 3; // wall width

union()
    {
 difference() {
 difference() {
difference() {
 difference() {
        //build a box
linear_extrude(height, convexity = 10) {
          offset(r = wallWidth)
          square([width, depth + (2 * depthSpace)], true);
        };
}
        // cut a working area space
        translate([0, 0, wallWidth]) linear_extrude(height, convexity = 10) square([width, depth], true);
}
        // cut a space on the sides of the working area
        // can be used to hold an excess wires
        for (i = [-1, 1])
          translate([0, i * (depth / 2 + depthSpace / 2), wallWidth]) linear_extrude(height, convexity = 10) square([width - 2 * depthSpace, depthSpace], true);
}
    // add the screw holes
    for (i = [
        [-1, 1],
        [1, -1],
        [-1, -1],
        [1, 1]
      ])
      translate([i[0] * (width / 2 - depthSpace / 2), i[1] * (depth / 2 + depthSpace / 2), height - 4 / 5 * height]) linear_extrude(4 / 5 * height, convexity = 10) circle(d = 2.5);
 
 
 
 
    // cut an indent at the upper edge of the box
    color("green") translate([0, 0, height - indentHeight])
    linear_extrude(indentHeight, convexity = 10) difference() {
      offset(r = wallWidth) square([width, depth + 2 * depthSpace], center = true);
      square([width + wallWidth, depth + 2 * depthSpace + wallWidth], center = true);
    }
}







        pcbScrewPositions = [
            [ 13.97, 2.54, wallWidth ],
            [ 15.24, 50.8, wallWidth ],
            [ 66.2, 35.56, wallWidth ],
            [ 66.2, 7.62, wallWidth ]
        ];
        // add screw hole insets
        for (i = pcbScrewPositions) {
            translate([ i[0], i[1], i[2] ]) cylinder(h = 2.5, r1 = 5.5 / 2, r2 = 4.5 / 2);
            translate([ i[0], i[1], i[2] + 2.5 ]) cylinder(h = 3, r = 1.2);
        }
    }









