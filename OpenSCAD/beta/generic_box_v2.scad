$fn=100;


aspen = "gray";
almond = "white";

pine = "green";
banyan="red";
altoSoporte = 3;


translate([-w/2-10,0,d+bpt+tpt])
rotate(a=180, v=[0,1,0])
lid();
translate([w/2+10,0,0])
box();


w=78;
h=56;
d=25;
wt=3.5;
bpt=5;
tpt=5;
cd=5;
cwt=1.5;

cx=0;
cy=0;
chs_i=1.5;
chs_o=4;
dsth=3;
chd_h=90;
chd_v=90;
tolerancia3D=0.3;
tolerancia=-0.2;
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
module lid()
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
            lid_hols();
            /*************************/

            //subtract here...

            lid_laterals_holes();
            /*************************/
	        lid_postes_holes_tuercas();
        }
    difference()
    {
        lid_postes();
	    lid_postes_holes();

    }
}

//bottom box
module box()
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
	// holes postes box
        tph_b_cut();
             box_laterals_holes();
        /*************************/

        //subtract here...

        /*************************/

    }
             //box_laterals_holes(); //preview
}

module box_laterals_holes()
{
    translate([cx,cy,0])
    {

        translate([+chd_h/2+-62,-34,23]) cube([35,10,8]);
        //translate([+chd_h/2-88,-10,20]) cube([9,19,11]);

    }

}
/****************************************************/
module lid_laterals_holes()
{
    translate([cx,cy,0])
    {
        // translate([+chd_h/2+6,-10,24]) cube([3,19,3]);
        translate([+chd_h/2-99,-10,24]) cube([3,19,5]);

    }
}
module lid_postes()
{

    translate([cx,cy,0])
    {

        //translate([+chd_h/2,chd_v/2-30,0])
        color(aspen) translate([+chd_h/2-18,chd_v/2-25.5,27]) cylinder(r=chs_o,h=altoSoporte+dsth);
        color(pine) translate([-chd_h/2+18,chd_v/2-25.5,27]) cylinder(r=chs_o,h=altoSoporte+dsth);
        //color() //translate([+chd_h/2,-chd_v/2,0]) cylinder(r=chs_o,h=bpt+dsth);
        color(almond) translate([+chd_h/2-18,-chd_v/2+25.5,27]) cylinder(r=chs_o,h=altoSoporte+dsth);
        color(banyan) translate([-chd_h/2+18,-chd_v/2+25.5,27]) cylinder(r=chs_o,h=altoSoporte+dsth);
        //echo("aca");
        //echo(dsth);

        //postes del centro
        //color(banyan) translate([-chd_h/2+45,-chd_v/2+60.5,27]) cylinder(r=chs_o,h=altoSoporte);
        //color(banyan) translate([-chd_h/2+45,-chd_v/2+60.5,25]) cylinder(r=1.9,h=2); //pin

        //color(pine) translate([-chd_h/2+45,-chd_v/2+30.5,27]) cylinder(r=chs_o,h=altoSoporte);
        //color(pine) translate([-chd_h/2+45,-chd_v/2+30.5,25]) cylinder(r=1.9,h=2); //pin

        // soportes board
        //color(banyan) translate([-chd_h/2+60,-chd_v/2+45.5,27]) cylinder(r=chs_o,h=altoSoporte);
        //color(pine) translate([-chd_h/2+30,-chd_v/2+45.5,27]) cylinder(r=chs_o,h=altoSoporte);



        //postes laterales
        //color(aspen) translate([-chd_h/2+1,-chd_v/2+53,27]) cylinder(r=chs_o-1,h=3);
        //color(aspen) translate([-chd_h/2+1,-chd_v/2+53,25]) cylinder(r=1.4,h=2);

        //color(almond) translate([-chd_h/2+1,-chd_v/2+39,27]) cylinder(r=chs_o-1,h=3);
        //color(almond) translate([-chd_h/2+1,-chd_v/2+39,25]) cylinder(r=1.4,h=2);

        //color(banyan) translate([-chd_h/2+92,-chd_v/2+53,27]) cylinder(r=chs_o-1,h=altoSoporte);
        //color(banyan) translate([-chd_h/2+92,-chd_v/2+53,25]) cylinder(r=1.4,h=2);

        //color(pine) translate([-chd_h/2+92,-chd_v/2+39,27]) cylinder(r=chs_o-1,h=altoSoporte);
        //color(pine) translate([-chd_h/2+92,-chd_v/2+39,25]) cylinder(r=1.4,h=5);
        //echo(chs_o);
        //color("red") translate([-chd_h/2+45,-chd_v/2+95,0]) cylinder(r=chs_o-5,h=bpt+dsth+100);
        //translate([-chd_h/2+40,-chd_v/2+55,0])
	//cylinder(r=chs_o-5,h=bpt+dsth+200);
    }


}

// Postes box
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
module lid_postes_holes_tuercas()
{
    translate([cx,cy,0])
    {

        translate([+chd_h/2-18,chd_v/2-25.5,35]) fhex(5.5,12);
        translate([-chd_h/2+18,chd_v/2-25.5,35]) fhex(5.5,12);
        translate([-chd_h/2+18,-chd_v/2+25.5,35]) fhex(5.5,12);
        translate([+chd_h/2-18,-chd_v/2+25.5,35]) fhex(5.5,12);

    }
}
module lid_postes_holes()
{
    translate([cx,cy,0])
    {

        // el tornillo tiene un diametro de 3 mas la tolerancia 0.3 => 3.3 / 2 = R
        translate([+chd_h/2-18,chd_v/2-25.5,24]) cylinder(r=1.65,h=bpt+dsth+2);
        translate([-chd_h/2+18,chd_v/2-25.5,24]) cylinder(r=1.65,h=bpt+dsth+2);
        translate([+chd_h/2-18,-chd_v/2+25.5,24]) cylinder(r=1.65,h=bpt+dsth+2);
        translate([-chd_h/2+18,-chd_v/2+25.5,24]) cylinder(r=1.65,h=bpt+dsth+2);
    }
}

module lid_hols()
{
    translate([cx1,cy1,0])
    {
        translate([-chd_v1/2, chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+tpt+3);
        translate([chd_v1/2, chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+tpt+3);

        translate([-chd_v1/2, -chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+tpt+3);
        translate([chd_v1/2, -chd_h1/2, -2])  cylinder(r=chs_i1,h=d+bpt+tpt+3);

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
        // translate([-chd_v1/2, chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+3);
        translate([-chd_v1/2, chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+3);
        translate([chd_v1/2, chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+3);

        translate([-chd_v1/2, -chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+3);
        translate([chd_v1/2, -chd_h1/2, -2]) cylinder(r=chs_i1,h=d+bpt+3);

        translate([-chd_v1/2, chd_h1/2, -1]) cylinder(r=3,h=4);

        translate([chd_v1/2, chd_h1/2, -1]) cylinder(r=3,h=4);

        translate([-chd_v1/2, -chd_h1/2, -1]) cylinder(r=3,h=4);

        translate([chd_v1/2, -chd_h1/2, -1]) cylinder(r=3,h=4);

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
