

// COPYRIGHT 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.


// view spatial 

DECLARE_ATTRIBUTE(0,viewmagnification,"Magnification factor")
DECLARE_ATTRIBUTE(0,viewprojectiontype,"projectiontype: 0=prespective, 1=orthographic")

DECLARE_ATTRIBUTE(0,viewpointradius,"Distance of camera from rotation point, or height above z plane in firstperson mode")
DECLARE_ATTRIBUTE(0,viewpointx,"Camera focus x co-ordinate")
DECLARE_ATTRIBUTE(0,viewpointy,"Camera focus y co-ordinate")
DECLARE_ATTRIBUTE(0,viewpointz,"Camera focus z co-ordinate")
DECLARE_ATTRIBUTE(0,viewpointrx,"Camera focus x rotation")
DECLARE_ATTRIBUTE(0,viewpointry,"Camera focus y rotation")
DECLARE_ATTRIBUTE(0,viewpointrz,"Camera focus z rotation")
DECLARE_ATTRIBUTE(90,viewfield,"Field-of-view angle in degrees")
DECLARE_ATTRIBUTE(90,viewnear,"Near clipping plane distance")
DECLARE_ATTRIBUTE(90,viewfar,"Far clipping plane distance")
DECLARE_ATTRIBUTE(90,viewfog,"Fog density factor: 0=none 1=max")
DECLARE_ATTRIBUTE(0,viewbackgroundcolor,"Contains red, green and blue nodes specifying background color")
DECLARE_ATTRIBUTE(0,viewconnectioncolor,"Contains red, green and blue nodes specifying connection color")
DECLARE_ATTRIBUTE(0,viewlabelcolor,"Contains red, green and blue nodes specifying label color")

DECLARE_ATTRIBUTE(0,viewlights,"Container for view lights nodes")

DECLARE_ATTRIBUTE(1,gridlinewidth,"Grid line wdth")
DECLARE_ATTRIBUTE(1,gridlinecolor,"Grid line color")
DECLARE_ATTRIBUTE(1,gridfog,"Grid fog density factor: 0=none 1=max")
DECLARE_ATTRIBUTE(1,gridx,"Grid x spacing")
DECLARE_ATTRIBUTE(1,gridy,"Grid y spacing")
DECLARE_ATTRIBUTE(1,gridz,"Grid z spacing")
DECLARE_ATTRIBUTE(1,gridplane,"Grid orientation (0-x/y, 1-x/z, 2-y/z)")
DECLARE_ATTRIBUTE(.1,connectorsize,"Connector size. Relative to space unit.")
DECLARE_ATTRIBUTE(1,connectorstyle,"Connector style.")
DECLARE_ATTRIBUTE(1,labelscale,"Magnification factor for display of object names.")

// view prefs

DECLARE_ATTRIBUTE(0,viewwindowsource,"View acts as a dragdrop source")
DECLARE_ATTRIBUTE(0,viewhideallconnectors,"Hide port connectors in view")
DECLARE_ATTRIBUTE(0,viewhidealllabels,"Hide object name display in view")
DECLARE_ATTRIBUTE(0,viewhideallbases,"Hide all object 2d shapes in view")
DECLARE_ATTRIBUTE(0,viewhidealldrawcontent,"Hide all object 3d shapes in view")
DECLARE_ATTRIBUTE(0,viewhiderouting,"Hide all object routing lines in view")
DECLARE_ATTRIBUTE(0,viewshowheads,"Hide all list heads and node indices in view")
DECLARE_ATTRIBUTE(0,viewautoconnect,"Disable object autocinnect in view")
DECLARE_ATTRIBUTE(0,viewsnaptogrid,"Disable gridsnap in view")
DECLARE_ATTRIBUTE(0,viewsyncupdate,"Disable repainting of all views when object editing is done")
DECLARE_ATTRIBUTE(0,viewignoreobjects,"Disable picking of objects in view")
DECLARE_ATTRIBUTE(0,viewshowgrid,"Disable showing of grid in view")
DECLARE_ATTRIBUTE(0,viewfirstperson,"Use firstperson camera mode in view")
DECLARE_ATTRIBUTE(0,viewlabelalignment,"Specify how object names are aligned relative to their 2d shapes: 0=bottom 1=center")
//DECLARE_ATTRIBUTE(0,viewinfoheight,"Specify how object info is aligned relative to their 3d shape height: 0 = on floor; 1 = with object")


// view appearance

DECLARE_ATTRIBUTE(1,assertupdate,"Try to repaint the window more often")
DECLARE_ATTRIBUTE(1,deassertupdate,"Try to repaint the window less often")

DECLARE_ATTRIBUTE(1,bitmap,"Window uses a bitmap instead of text")
DECLARE_ATTRIBUTE(1,beveltype,"Specifies the bevel type of a Panel-type view component: 0,1,2,3")
DECLARE_ATTRIBUTE(64,cellwidth,"Cellwidth in pixels")
DECLARE_ATTRIBUTE(64,cellheight,"Cellheight in pixels")
DECLARE_ATTRIBUTE(0,grayed,"Window is grayed")
DECLARE_ATTRIBUTE(0,hidden,"Window is hidden")
DECLARE_ATTRIBUTE(1,initialtext,"Initial view text")
DECLARE_ATTRIBUTE(0,items,"Items list")
DECLARE_ATTRIBUTE(0,itemcurrent,"Currently selected item")
DECLARE_ATTRIBUTE(1,palettewindow,"The window is a palette window")
DECLARE_ATTRIBUTE(1,documentwindow,"The window is a document window")
DECLARE_ATTRIBUTE(1,tabwindow,"The window can combine with other tabwindows")
DECLARE_ATTRIBUTE(0,statusbar,"Window has a statusbar")
DECLARE_ATTRIBUTE(0,tooltip,"Window has a tooltip")
//DECLARE_ATTRIBUTE(0,menumain,"Main menu")
DECLARE_ATTRIBUTE(0,menuview,"Switch: if zero, disable the standard view menu")
DECLARE_ATTRIBUTE(0,menucustom,"Contains the definition of a custom menu for the view")
DECLARE_ATTRIBUTE(0,menupopup,"Contains the definition of a custom popup menu for the view")

DECLARE_ATTRIBUTE(1,noformat,"Do not apply flexscritpt formatting to editor")
DECLARE_ATTRIBUTE(1,wordwrap,"Specify wrapping text in the editor: 0=no wrapping")
DECLARE_ATTRIBUTE(1,style, "Define window style using standard windows styles")
DECLARE_ATTRIBUTE(1,exstyle, "Define extended window style using standard windows styles")

DECLARE_ATTRIBUTE(0,viewwindowopen,"Window open state")
DECLARE_ATTRIBUTE(0,viewwindowtype,"Window type: Refer to help file for more details")
DECLARE_ATTRIBUTE(0,viewwindowclean,"Specifies that when the window is closed, the underlying view tree is to be deleted")
DECLARE_ATTRIBUTE(0,viewfull,"Specifies that the window has no title bar")
DECLARE_ATTRIBUTE(0,windowtitle,"Text string for window title, otherwise the viewfocus path is used")


// view align

DECLARE_ATTRIBUTE(0,alignrightmargin,"Pixels to stay from right edge of parent")
DECLARE_ATTRIBUTE(0,alignbottommargin,"Pixels to stay from bottom edge of parent")
DECLARE_ATTRIBUTE(0,alignrightposition,"Pixels to position from right edge of parent")
DECLARE_ATTRIBUTE(0,alignbottomposition,"Pixels to position from bottom edge of parent")
DECLARE_ATTRIBUTE(0,aligncenterx,"Position at horizontal center of parent")
DECLARE_ATTRIBUTE(0,aligncentery,"Position at vertical center of parent")


// view gui links

DECLARE_ATTRIBUTE(0,objectfocus,"Node text path of edited (clicked) object")
DECLARE_ATTRIBUTE(0,viewfocus,"Node text path of view's natural viewed object type")
DECLARE_ATTRIBUTE(0,undohistory,"Attribute specifying undo history information ")


// view gui events

DECLARE_ATTRIBUTE(1,OnPress,"Node function executed on button press")
DECLARE_ATTRIBUTE(1,OnSelect,"Node function executed on selection made")
DECLARE_ATTRIBUTE(1,OnPreOpen,"Node function executed before opening of window")
DECLARE_ATTRIBUTE(1,OnOpen,"Node function executed on opening of window")
DECLARE_ATTRIBUTE(1,OnClose,"Node function executed on closing of window")
DECLARE_ATTRIBUTE(1,OnKeyDown,"Node function executed on keypress")
DECLARE_ATTRIBUTE(1,OnKeyUp,"Node function executed on key release")
DECLARE_ATTRIBUTE(1,OnDropFile,"Node function executed on file drop")
DECLARE_ATTRIBUTE(1,OnDrop,"Node function executed on object drop")
DECLARE_ATTRIBUTE(1,OnDropNode,"Node function executed on object drop into object")
DECLARE_ATTRIBUTE(1,OnMouseButtonDown,"Node function executed on mouse event")
DECLARE_ATTRIBUTE(1,OnMouseButtonUp,"Node function executed on mouse event")
DECLARE_ATTRIBUTE(1,OnMouseWheel,"Node function executed on mouse event")
DECLARE_ATTRIBUTE(0,OnMouseMove,"Function node executed on change of mouse position")
DECLARE_ATTRIBUTE(1,OnStick,"Node function executed on stick event")
DECLARE_ATTRIBUTE(1,OnActivateNotify,"Node function executed on changing the active window")
DECLARE_ATTRIBUTE(1,OnFocus,"Node function executed on focus lost")
DECLARE_ATTRIBUTE(1,OnKillFocus,"Node function executed on focus lost")
DECLARE_ATTRIBUTE(1,OnSize,"Node function executed on window size")
DECLARE_ATTRIBUTE(0,OnMenuPopup,"Attribute fired on menu popup")
DECLARE_ATTRIBUTE(0,OnLoad,"Function node executed once the DOM of an html widget is loaded")


// view data links

DECLARE_ATTRIBUTE(1,hotlink,"Node path to node-data to dynamically displayed")
DECLARE_ATTRIBUTE(1,coldlink,"Node path to node-data to be statically displayed")
DECLARE_ATTRIBUTE(1,hotlinkname,"Node path to node-name to dynamically displayed")
DECLARE_ATTRIBUTE(1,coldlinkname,"Node path to node-name to statically displayed")

DECLARE_ATTRIBUTE(1,hotlinkx,"Node expression to node-data to dynamically displayed")
DECLARE_ATTRIBUTE(1,coldlinkx,"Node expression to node-data to be statically displayed")
DECLARE_ATTRIBUTE(1,hotlinknamex,"Node expression to node-name to dynamically displayed")
DECLARE_ATTRIBUTE(1,coldlinknamex,"Node expression to node-name to statically displayed")

DECLARE_ATTRIBUTE(0,customaction,"User custom settings. Typically to override automatic actions.")

// scrollers

DECLARE_ATTRIBUTE(0,rangemin,"Scroll bar range minimum")
DECLARE_ATTRIBUTE(1,rangemax,"Scroll bar range maximum")
DECLARE_ATTRIBUTE(1,rangeexp,"Exponent of scroll bar value")


// view picklists

DECLARE_ATTRIBUTE(1,picklist,"Node path to picklist")
DECLARE_ATTRIBUTE(1,pickitem,"Index to picked item")
DECLARE_ATTRIBUTE(1,pickprimary,"Node path to initial picked option")
DECLARE_ATTRIBUTE(1,pickcopydataonly,"Only copy back picked data, not name")
DECLARE_ATTRIBUTE(1,picklistnameonly,"Only copy back picked name, not data")
DECLARE_ATTRIBUTE(1,pagelist,"Node path to list of node paths for dynamic tab pages")


// view graphs

DECLARE_ATTRIBUTE(1,graphxy,"Graph treats data as x-y format")
DECLARE_ATTRIBUTE(1,graphstep,"Draw graph lines as discrete steps")
DECLARE_ATTRIBUTE(1,graphbars,"Draw graph vertical bars")
DECLARE_ATTRIBUTE(1,graphlines,"Draw graph lines")
DECLARE_ATTRIBUTE(1,graphpoints,"Draw graph points")
DECLARE_ATTRIBUTE(1,graphgrid,"Draw graph background grid")
DECLARE_ATTRIBUTE(1,graphaxes,"Draw graph axes")
DECLARE_ATTRIBUTE(1,graphlegend,"Draw graph legend")
DECLARE_ATTRIBUTE(1,graphlegendhisto,"Draw graph legend as/from histogram")
DECLARE_ATTRIBUTE(1,graphannotate,"Draw graph annotation")
DECLARE_ATTRIBUTE(1,graphpie,"Draw graph as pie")
DECLARE_ATTRIBUTE(1,graphpiedata,"Node path to pie chart data")
DECLARE_ATTRIBUTE(1,graphmaxpoints,"Maximum points to draw on graph")
DECLARE_ATTRIBUTE(1,graphtitle,"Text for graph title")
DECLARE_ATTRIBUTE(1,graphhistodata,"Node path to histogram data")


DECLARE_ATTRIBUTE(1,treeiconsilentobject,"")

DECLARE_ATTRIBUTE(1,viewfont,"Specify view's font")

DECLARE_ATTRIBUTE(0,treeicontitle,"displayed name in tree, no editing")
DECLARE_ATTRIBUTE(0,treeiconindex,"displayed icon in tree, index based")
DECLARE_ATTRIBUTE(0,treeiconhide,"hide icon in tree")

DECLARE_ATTRIBUTE(0,description,"Full description")
DECLARE_ATTRIBUTE(0,picture,"Iconic bitmap")
DECLARE_ATTRIBUTE(0,title,"Descriptive title")

DECLARE_ATTRIBUTE(0,packedmedia,"contains used media files")

// COPYRIGHT 2006   F L E X S I M   C O R P O R A T I O N .  ALL RIGHTS RESERVED.

