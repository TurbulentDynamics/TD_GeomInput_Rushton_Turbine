[image]
data=dlmread('updated_tank_geometry.csv');

%scatter3(data(:,10), data(:,12), data(:,14), 1, 5)

 x = data(:, 1);
 y = data(:, 2);
 z = data(:, 3);

 c = data(:, 4);

 
 y = 200 - y;


scatter3(z, x, y, 1, c)

%camup([0 1 0])
% set(h.axes,'YDir','reverse')    

axis equal
grid

xlabel('x');
ylabel('z');
zlabel('y');

print('filename.png', '-dpng', '-S1280,720');
