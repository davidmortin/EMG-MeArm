syms xd0 yd0 zd0 real


xd = xd0-7.1;
yd = yd0-1.85;
zd = zd0-1;

th1=atan(-xd/yd);
th1=(th1*180)/(pi)

xp=.72111*(-sin(th1-33.69));
yp=.72111*(-(cos(th1-33.69)));
zp=1.62;

d1 = sqrt((xd-xp)^2+(yd-yp)^2);
d2 = d1-1.88;
d3 = sqrt((zd-zp)^2+d2^2);

th2 = 2*asin(.5*d3/3.25);
th2 = (th2*180)/(pi)-90

thz = 0.5*(180-(th2+90)); %angle between first limb and d3 in degrees
thr = asin((zd-zp)/d3)*180/pi; %angle between d3 and horizontal in degrees
th3 = 90-(thz+thr)


matlabFunction(th1,'File','th1DJM','vars',{[xd0 yd0 zd0]})
matlabFunction(th2,'File','th2DJM','vars',{[xd0 yd0 zd0]})
matlabFunction(th3,'File','th3DJM','vars',{[xd0 yd0 zd0]})