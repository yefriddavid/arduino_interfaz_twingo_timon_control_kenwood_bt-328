$fn=100;




translate([-w/2-10,0,d+bpt+tpt])
rotate(a=180, v=[0,1,0])
box_top();
translate([w/2+10,0,0])
box_bottom();
             

//*************************************************//
//PARAMETERS
//*************************************************//
//BOX
//--------------------------------------------------
//inner box width + tolerances
//w=120;
w=105;
//inner box length + tolerances
h=40;
// h=150;
//inner box depth 
d=25;
//wall tickness
wt=3.5;
//bottom plate tickness
bpt=5;
//top plate tickness
tpt=5;
//top cutout depth
cd=5;
//top cutout tickness
cwt=1.5;
//--------------------------------------------------
//BOARD MOUNTING HOLES
//--------------------------------------------------
//position
cx=0;
cy=0;
//holes size (radius)
chs_i=1.5;
chs_o=4;
//distancer height
dsth=3;
//holes distance h
chd_h=90;
//holes distance v
chd_v=90;
//--------------------------------------------------
//TOP PART MOUNTING HOLES
//--------------------------------------------------
//position
cx1=0;
cy1=0;
//holes size (radius)
chs_i1=1.6;
chs_o1=3;
//holes distance h
chd_h1=h-2*chs_i1-2;
//holes distance v
chd_v1=w-2*chs_i1-2;
//*************************************************//
//*************************************************//
//MODULES
//*************************************************//

//top box part          
module box_top()
{
        difference()
        {
            union()
            {
                difference()
                {
                    translate([ 0, 0, d+bpt-cd-0.2])     
                    rounded_cube( w+2*wt, h+2*wt, tpt+cd+0.2, 6);
                    
                    translate([ 0, 0,  d+bpt-cd-1])
                    rounded_cube( w+2*cwt+0.3, h+2*cwt+0.3, cd+1, 4);
                }
                /*************************/
                
                //add here...
                
                /*************************/
            }
            //TOP PART HOLES
            tph_t_cut();
            /*************************/
            
            //subtract here... 
            
            /*************************/ 
        }
            board_distancer();
bh_cut();
}
//bottom box
module box_bottom()
{
    difference()
    {
        union()
        {
            difference()
            {
                rounded_cube( w+2*wt, h+2*wt, d+bpt, 6);
                
                translate([ 0, 0, -cd])
                difference()
                {
                    translate([ 0, 0,  d+bpt])
                    rounded_cube( w+2*wt+1, h+2*wt+1, cd+1, 4);

                    translate([ 0, 0,  d+bpt-1])
                    rounded_cube( w+2*cwt, h+2*cwt, cd+3, 4);
                }
                translate([ 0, 0, bpt])
                rounded_cube( w, h, d+bpt, 4);
            }
            //BOARD DISTANCER
            //board_distancer();
            //TOP PLATE DISTANCER
            top_distancer();
            /*************************/
            
            //add here...
            
            /*************************/
        }
        
        //BOARD HOLES
        // bh_cut();
        //TOP PART HOLES
        tph_b_cut();
        /*************************/
        
        //subtract here...
        
        /*************************/
  
    }
}

/****************************************************/
module board_distancer()
{
    translate([cx,cy,0])
    {              
        //translate([+chd_h/2,chd_v/2-30,0])
        translate([+chd_h/2-10,chd_v/2-35,25]) cylinder(r=chs_o,h=bpt+dsth);

        translate([-chd_h/2+10,chd_v/2-35,25]) cylinder(r=chs_o,h=bpt+dsth);
        //translate([+chd_h/2,-chd_v/2,0]) cylinder(r=chs_o,h=bpt+dsth);
        translate([+chd_h/2-10,-chd_v/2+35,25]) cylinder(r=chs_o,h=bpt+dsth);
        translate([-chd_h/2+10,-chd_v/2+35,25]) cylinder(r=chs_o,h=bpt+dsth);

	//center
        translate([-chd_h/2+40,-chd_v/2+55,27]) cylinder(r=chs_o,h=bpt+dsth);
        translate([-chd_h/2+40,-chd_v/2+55,20]) cylinder(r=chs_o-2,h=bpt+dsth);

        translate([-chd_h/2+40,-chd_v/2+35,27]) cylinder(r=chs_o,h=bpt+dsth);
        translate([-chd_h/2+40,-chd_v/2+35,20]) cylinder(r=chs_o-2,h=bpt+dsth);

        //color("red") translate([-chd_h/2+45,-chd_v/2+95,0]) cylinder(r=chs_o-5,h=bpt+dsth+100);
        //translate([-chd_h/2+40,-chd_v/2+55,0]) 
	//cylinder(r=chs_o-5,h=bpt+dsth+200);

    }
}
module top_distancer()
{
    translate([cx1,cy1,0])
    {
        translate([-chd_v1/2, chd_h1/2, 0])   
        cylinder(r=chs_o1,h=d+bpt);
        translate([-chd_v1/2, -chd_h1/2, 0])   
        cylinder(r=chs_o1,h=d+bpt);
        translate([chd_v1/2, chd_h1/2, 0])   
        cylinder(r=chs_o1,h=d+bpt);
        translate([chd_v1/2, -chd_h1/2, 0])   
        cylinder(r=chs_o1,h=d+bpt);
    }
}
module bh_cut()
{
    translate([cx,cy,0])
    {  
        // translate([+chd_h/2-140,chd_v/2-35,-1]) cylinder(r=chs_i,h=bpt+dsth+2);
        translate([+chd_h/2-5,chd_v/2-35,20]) cylinder(r=chs_i,h=bpt+dsth+2);
        translate([-chd_h/2-120,chd_v/2-35,-1]) cylinder(r=chs_i,h=bpt+dsth+2);
        translate([+chd_h/2-140,-chd_v/2+35,-1]) cylinder(r=chs_i,h=bpt+dsth+2);
        translate([-chd_h/2-120,-chd_v/2+35,-1]) cylinder(r=chs_i,h=bpt+dsth+2);
        // translate([+chd_h/2,-chd_v/2,-1]) cylinder(r=chs_i,h=bpt+dsth+2);
        
        //translate([+chd_h/2-10,chd_v/2-35,30]) fhex(5.5,3);
        //translate([-chd_h/2+20,chd_v/2-35,30]) fhex(5.5,3);
        //translate([-chd_h/2+20,-chd_v/2+35,30]) fhex(5.5,3);
        translate([+chd_h/2-20,-chd_v/2+35,30]) fhex(5.5,3);

    }
}

module tph_t_cut()
{
    translate([cx1,cy1,0])
    {
        translate([-chd_v1/2, chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+tpt+3);
        translate([chd_v1/2, chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+tpt+3);
    
        translate([-chd_v1/2, -chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+tpt+3);
        translate([chd_v1/2, -chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+tpt+3);
        
        translate([-chd_v1/2, chd_h1/2, d+bpt+tpt-1.3]) 
        fhex(5.5,3);
        
        translate([chd_v1/2, chd_h1/2, d+bpt+tpt-1.3])  
        fhex(5.5,3);
    
        translate([-chd_v1/2, -chd_h1/2, d+bpt+tpt-1.3])   
        fhex(5.5,3);
        
        translate([chd_v1/2, -chd_h1/2, d+bpt+tpt-1.3])   
        fhex(5.5,3);
    
    }   
}
module tph_b_cut()
{
    translate([cx1,cy1,0])
    {
        translate([-chd_v1/2, chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+3);
        translate([chd_v1/2, chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+3);
    
        translate([-chd_v1/2, -chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+3);
        translate([chd_v1/2, -chd_h1/2, -2])   
        cylinder(r=chs_i1,h=d+bpt+3);
        
        translate([-chd_v1/2, chd_h1/2, -1]) 
        cylinder(r=3,h=4);
        
        translate([chd_v1/2, chd_h1/2, -1])  
        cylinder(r=3,h=4);
    
        translate([-chd_v1/2, -chd_h1/2, -1])   
        cylinder(r=3,h=4);
        
        translate([chd_v1/2, -chd_h1/2, -1])   
        cylinder(r=3,h=4); 
    
    }   
}


module rounded_cube( x, y, z, r)
{
    translate([-x/2+r,-y/2+r,0])
    linear_extrude(height=z)
    minkowski() 
    {
        square([x-2*r,y-2*r],true);
        translate([x/2-r,y/2-r,0])
        circle(r);

    }
}

module fhex(wid,height)
{
    hull()
    {
        cube([wid/1.7,wid,height],center = true);
        rotate([0,0,120])cube([wid/1.7,wid,height],center = true);
        rotate([0,0,240])cube([wid/1.7,wid,height],center = true);
    }
}
