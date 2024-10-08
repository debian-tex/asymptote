import graph3;
import grid3;
import palette;

size(400,300,IgnoreAspect);

currentprojection=orthographic(dir(50,50));

real f(pair z) {return cos(2*pi*z.x)*sin(2*pi*z.y);}

surface s=surface(f,(-1/2,-1/2),(1/2,1/2),50,Spline);

surface S=planeproject(unitsquare3)*s;
S.colors(palette(s.map(zpart),Rainbow()));
draw(S,nolight);
draw(s,lightgray+opacity(0.7),render(tessellate=false));

grid3(XYZgrid);
