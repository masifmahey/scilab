// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Antoine ELIAS
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->


function fig = createFigure(layout)
    fig = scf();
    fig.layout = layout;
    fig.toolbar_visible = "off";
    fig.menubar_visible = "off";
    fig.infobar_visible = "off";
endfunction

//constraints

//no border
createFigure("none");

c = createConstraints("nolayout");
u = uicontrol("constraints", c);
assert_checkequal(u.constraints, c);

delete(gcf());

//border layout
createFigure("border");

c = createConstraints("border", "center");
u = uicontrol("constraints", c, "string", "center");
assert_checkequal(u.constraints, c);

c = createConstraints("border", "left");
u = uicontrol("constraints", c, "string", "left");
assert_checkequal(u.constraints, c);

c = createConstraints("border", "right");
u = uicontrol("constraints", c, "string", "right");
assert_checkequal(u.constraints, c);

c = createConstraints("border", "top");
u = uicontrol("constraints", c, "string", "top");
assert_checkequal(u.constraints, c);

c = createConstraints("border", "bottom");
u = uicontrol("constraints", c, "string", "bottom");
assert_checkequal(u.constraints, c);

delete(gcf());

//grid layout
createFigure("grid");

c = createConstraints("grid");
u = uicontrol("constraints", c);
assert_checkequal(u.constraints, c);

delete(gcf());

//gridbag layout
createFigure("gridbag");

c = createConstraints("gridbag", [1 2 3 4]);
u = uicontrol("constraints", c);
assert_checkequal(u.constraints, c);

c = createConstraints("gridbag", [1 2 3 4], [1.1 2.1]);
u = uicontrol("constraints", c);
assert_checkequal(u.constraints, c);

c = createConstraints("gridbag", [1 2 3 4], [1.1 2.1], "both");
u = uicontrol("constraints", c);
assert_checkequal(u.constraints, c);

c = createConstraints("gridbag", [1 2 3 4], [1.1 2.1], "both", "lower_left");
u = uicontrol("constraints", c);
assert_checkequal(u.constraints, c);

c = createConstraints("gridbag", [1 2 3 4], [1.1 2.1], "both", "lower_left", [10 20]);
u = uicontrol("constraints", c);
assert_checkequal(u.constraints, c);

delete(gcf());


// options
createFigure("none");
f = gcf();
assert_checkequal(f.layout_options, createLayoutOptions("nolayout"));
f.layout_options = createLayoutOptions("none");
assert_checkequal(f.layout_options, createLayoutOptions("none"));
delete(gcf());

createFigure("gridbag");
f = gcf();
assert_checkequal(f.layout_options, createLayoutOptions("gridbag"));
f.layout_options = createLayoutOptions("gridbag");
assert_checkequal(f.layout_options, createLayoutOptions("gridbag"));
delete(gcf());

createFigure("border");
f = gcf();
assert_checkequal(f.layout_options, createLayoutOptions("border"));

f.layout_options = createLayoutOptions("border", [10,20]);
assert_checkequal(f.layout_options, createLayoutOptions("border", [10,20]));
delete(gcf());

createFigure("grid");
f = gcf();
assert_checkequal(f.layout_options, createLayoutOptions("grid"));

f.layout_options = createLayoutOptions("grid", [30,40]);
assert_checkequal(f.layout_options, createLayoutOptions("grid", [30,40]));

f.layout_options = createLayoutOptions("grid", [10,20], [30,40]);
assert_checkequal(f.layout_options, createLayoutOptions("grid", [10,20], [30,40]));
delete(gcf());
