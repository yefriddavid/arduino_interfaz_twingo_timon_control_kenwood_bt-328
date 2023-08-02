 // create cover box

    
    
$fn = 100; // resolution
clearance=0.25; //clearances for 3D printing to make parts easily fit where needed
//width = 68.6+3; //width of the case(X)
depth = 53.3+3; //depth of the case (Y)
width=105;
depthSpace = 5; //little space on both sides of the case to store loose wires and make it easier to fit components
height = 35; //height of the case (Z)
indentHeight = 2; // tells us how far the cover overlaps the case
wallWidth = 3; // wall width

union(){
    
    difference() {
    // tapa solita
        linear_extrude(wallWidth + indentHeight, convexity = 10) {
          offset(r = wallWidth)
          square([width, depth + (2 * depthSpace)], true);
        };
        
        // Parte interna de la tapa
        difference() {

            // linear_extrude(indentHeight, convexity = 10) 
            // square([width + wallWidth + clearance, depth + 2 * depthSpace + wallWidth + clearance], center = true);
        //translate([0,0, 0]) 
            square([width + wallWidth + clearance, depth + 2 * depthSpace + wallWidth + clearance], center = true);
        }
        
        // huecos para tornillos
        for (i = [
            [-1, 1],
            [1, -1], 
            [-1, -1],
            [1, 1]
        ])
        translate([i[0] * (width / 2 - depthSpace / 2), i[1] * (depth / 2 + depthSpace / 2), 0]) 
        linear_extrude(wallWidth + indentHeight, convexity = 10) circle(d = 2.5);
        
        
    }
  
      
          pcbScrewPositions = [
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
            translate([ i[0], i[1], i[2] ]) cylinder(h = 2.5, r1 = 5.5 / 2, r2 = 4.5 / 2); // base
            translate([ i[0], i[1], i[2] + 2.5 ]) cylinder(h = 3, r = 1.2); // jump
        }
        
        
        
        // postes para tornillos
        pcbScrewPositions1 = [
            [ 22.97, -5.54, wallWidth ],
            [ -22.97, -5.54, wallWidth ],
        ];

        for (i = pcbScrewPositions1) {
            color("red") translate([ i[0], i[1], i[2] ]) cylinder(h = 2.5, r = 3.2);
            color("red") translate([ i[0], i[1], i[2] + 2.5 ]) cylinder(h = 4, r = 2.2);
        }    
        
        
                /*for (i = [
            //[-1, 1],
            //[1, -1], 
            [-1, -1],
            [1, 1]
          ])
          translate([i[0] * (width / 2 - depthSpace / 2), i[1] * (depth / 2 + depthSpace / 2), 0]) 
            linear_extrude(wallWidth + indentHeight, convexity = 10) circle(d = 2.5);
            */
            
            
          /*difference() {  
            
    for (i = [
        //[-1, 1],
        //[1, -1], 
        [-1, -1],
        [1, 1]
      ])
      translate([i[0] * (width / 2 - depthSpace / 2), i[1] * (depth / 2 + depthSpace / 2), 0]) 
        linear_extrude(wallWidth + indentHeight, convexity = 10) circle(d = 12.5);
  }*/


  
  }
  
  
  
    
    
    
    
    
    
    
    
    
