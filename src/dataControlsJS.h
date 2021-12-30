const char JS_CONTROLS[] PROGMEM = R"=====(
const UI_INITIAL_GUI=200;const UI_RELOAD=201;const UPDATE_OFFSET=100;const UI_TITEL=0;const UI_PAD=1;const UPDATE_PAD=101;const UI_CPAD=2;const UPDATE_CPAD=102;const UI_BUTTON=3;const UPDATE_BUTTON=103;const UI_LABEL=4;const UPDATE_LABEL=104;const UI_SWITCHER=5;const UPDATE_SWITCHER=105;const UI_SLIDER=6;const UPDATE_SLIDER=106;const UI_NUMBER=7;const UPDATE_NUMBER=107;const UI_TEXT_INPUT=8;const UPDATE_TEXT_INPUT=108;const UI_GRAPH=9;const ADD_GRAPH_POINT=10;const CLEAR_GRAPH=109;const UI_TAB=11;const UPDATE_TAB=111;const UI_SELECT=12;const UPDATE_SELECT=112;const UI_OPTION=13;const UPDATE_OPTION=113;const UI_MIN=14;const UPDATE_MIN=114;const UI_MAX=15;const UPDATE_MAX=115;const UI_STEP=16;const UPDATE_STEP=116;const UI_GAUGE=17;const UPDATE_GAUGE=117;const UI_ACCEL=18;const UPTDATE_ACCEL=117;const UP=0;const DOWN=1;const LEFT=2;const RIGHT=3;const CENTER=4;const C_TURQUOISE=0;const C_EMERALD=1;const C_PETERRIVER=2;const C_WETASPHALT=3;const C_SUNFLOWER=4;const C_CARROT=5;const C_ALIZARIN=6;const C_DARK=7;const C_NONE=255;var graphData=new Array();var hasAccel=false;var sliderContinuous=false;function colorClass(colorId){colorId=Number(colorId);switch(colorId){case C_TURQUOISE:return"turquoise";case C_EMERALD:return"emerald";case C_PETERRIVER:return"peterriver";case C_WETASPHALT:return"wetasphalt";case C_SUNFLOWER:return"sunflower";case C_CARROT:return"carrot";case C_ALIZARIN:return"alizarin";case C_NONE:return"dark";default:return"";}}
var websock;var websockConnected=false;function requestOrientationPermission(){}
function saveGraphData(){localStorage.setItem("espuigraphs",JSON.stringify(graphData));}
function restoreGraphData(id){var savedData=localStorage.getItem("espuigraphs",graphData);if(savedData!=null){savedData=JSON.parse(savedData);return savedData[id];}
return[];}
function restart(){$(document).add("*").off();$("#row").html("");websock.close();start();}
function conStatusError(){websockConnected=false;$("#conStatus").removeClass("color-green");$("#conStatus").addClass("color-red");$("#conStatus").html("Error / No Connection &#8635;");$("#conStatus").off();$("#conStatus").on({click:restart,});}
function handleVisibilityChange(){if(!websockConnected&&!document.hidden){restart();}}
function start(){document.addEventListener("visibilitychange",handleVisibilityChange,false);if(window.location.port!=""||window.location.port!=80||window.location.port!=443){websock=new WebSocket("ws://"+window.location.hostname+":"+window.location.port+"/ws");}else{websock=new WebSocket("ws://"+window.location.hostname+"/ws");}
websock.onopen=function(evt){console.log("websock open");$("#conStatus").addClass("color-green");$("#conStatus").text("Connected");websockConnected=true;};websock.onclose=function(evt){console.log("websock close");conStatusError();};websock.onerror=function(evt){console.log(evt);conStatusError();};var handleEvent=function(evt){console.log(evt);var data=JSON.parse(evt.data);var e=document.body;var center="";var style="";if(data.hasOwnProperty('inlineStyle')){style=' style="'+data.inlineStyle+'" ';}
switch(data.type){case UI_INITIAL_GUI:$("#row").html("");$("#tabsnav").html("");$("#tabscontent").html("");if(data.sliderContinuous){sliderContinuous=data.sliderContinuous;}
data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element),};handleEvent(fauxEvent);});break;case UI_RELOAD:window.location.reload();break;case UI_TITEL:document.title=data.label;$("#mainHeader").html(data.label);break;case UI_LABEL:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<span id='l"+
data.id+
"' class='label label-wrap'>"+
data.value+
"</span>"+
"</div>");}
break;case UI_BUTTON:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' class='one columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<button id='btn"+
data.id+
"' "+style+
"onmousedown='buttonclick("+
data.id+
", true)' "+
"onmouseup='buttonclick("+
data.id+
", false)'>"+
data.value+
"</button></div>");$("#btn"+data.id).on({touchstart:function(e){e.preventDefault();buttonclick(data.id,true);},touchend:function(e){e.preventDefault();buttonclick(data.id,false);},});}
break;case UI_SWITCHER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='one columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<label id='sl"+
data.id+
"' class='switch "+
(data.value=="1"?"checked":"")+
"'>"+
"<div class='in'><input type='checkbox' id='s"+
data.id+
"' onClick='switcher("+
data.id+
",null)' "+
(data.value=="1"?"checked":"")+
"/></div>"+
"</label>"+
"</div>");switcher(data.id,data.value);}
break;case UI_CPAD:case UI_PAD:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<nav class='control'>"+
"<ul>"+
"<li><a onmousedown='padclick(UP, "+
data.id+
", true)' onmouseup='padclick(UP, "+
data.id+
", false)' id='pf"+
data.id+
"'>&#9650;</a></li>"+
"<li><a onmousedown='padclick(RIGHT, "+
data.id+
", true)' onmouseup='padclick(RIGHT, "+
data.id+
", false)' id='pr"+
data.id+
"'>&#9650;</a></li>"+
"<li><a onmousedown='padclick(LEFT, "+
data.id+
", true)' onmouseup='padclick(LEFT, "+
data.id+
", false)' id='pl"+
data.id+
"'>&#9650;</a></li>"+
"<li><a onmousedown='padclick(DOWN, "+
data.id+
", true)' onmouseup='padclick(DOWN, "+
data.id+
", false)' id='pb"+
data.id+
"'>&#9650;</a></li>"+
"</ul>"+
(data.type==UI_CPAD?"<a class='confirm' onmousedown='padclick(CENTER,"+
data.id+
", true)' onmouseup='padclick(CENTER, "+
data.id+
", false)' id='pc"+
data.id+
"'>OK</a>":"")+
"</nav>"+
"</div>");$("#pf"+data.id).on({touchstart:function(e){e.preventDefault();padclick(UP,data.id,true);},touchend:function(e){e.preventDefault();padclick(UP,data.id,false);},});$("#pl"+data.id).on({touchstart:function(e){e.preventDefault();padclick(LEFT,data.id,true);},touchend:function(e){e.preventDefault();padclick(LEFT,data.id,false);},});$("#pr"+data.id).on({touchstart:function(e){e.preventDefault();padclick(RIGHT,data.id,true);},touchend:function(e){e.preventDefault();padclick(RIGHT,data.id,false);},});$("#pb"+data.id).on({touchstart:function(e){e.preventDefault();padclick(DOWN,data.id,true);},touchend:function(e){e.preventDefault();padclick(DOWN,data.id,false);},});$("#pc"+data.id).on({touchstart:function(e){e.preventDefault();padclick(CENTER,data.id,true);},touchend:function(e){e.preventDefault();padclick(CENTER,data.id,false);},});}
break;case UI_SLIDER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter card-slider "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<div class='range-slider'>"+
"<input id='sl"+
data.id+
"' type='range' min='0' max='100' value='"+
data.value+
"' class='range-slider__range'>"+
"<span class='range-slider__value'>"+
data.value+
"</span>"+
"</div>"+
"</div>");rangeSlider(!sliderContinuous);}
break;case UI_NUMBER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<input style='color:black;' id='num"+
data.id+
"' type='number' value='"+
data.value+
"' onchange='numberchange("+
data.id+
")' />"+
"</div>");}
break;case UI_TEXT_INPUT:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<input style='color:black;' id='text"+
data.id+
"' value='"+
data.value+
"' onchange='textchange("+
data.id+
")' />"+
"</div>");}
break;case UI_TAB:if(data.visible){$("#tabsnav").append("<li><a onmouseup='tabclick("+data.id+")' href='#tab"+data.id+"'>"+data.value+"</a></li>");$("#tabscontent").append("<div id='tab"+data.id+"'></div>");tabs=$(".tabscontent").tabbedContent({loop:true}).data("api");$("a").filter(function(){return $(this).attr("href")==="#click-to-switch";}).on("click",function(e){var tab=prompt("Tab to switch to (number or id)?");if(!tabs.switchTab(tab)){alert("That tab does not exist :\\");}
e.preventDefault();});}
break;case UI_SELECT:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<select style='color:black;' id='select"+
data.id+
"' onchange='selectchange("+
data.id+
")' />"+
"</div>");}
break;case UI_OPTION:if(data.parentControl){var parent=$("#select"+data.parentControl);parent.append("<option id='option"+
data.id+
"' "+style+" value='"+
data.value+
"' "+
data.selected+
">"+
data.label+
"</option>");}
break;case UI_MIN:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){parent.attr("min",data.value);}}
break;case UI_MAX:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){parent.attr("max",data.value);}}
break;case UI_STEP:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){parent.attr("step",data.value);}}
break;case UI_GRAPH:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<figure id='graph"+
data.id+
"'>"+
"<figcaption>"+
data.label+
"</figcaption>"+
"</figure>"+
"</div>");graphData[data.id]=restoreGraphData(data.id);renderGraphSvg(graphData[data.id],"graph"+data.id);}
break;case ADD_GRAPH_POINT:var ts=Math.round(new Date().getTime()/1000);graphData[data.id].push({x:ts,y:data.value});saveGraphData();renderGraphSvg(graphData[data.id],"graph"+data.id);break;case CLEAR_GRAPH:graphData[data.id]=[];saveGraphData();renderGraphSvg(graphData[data.id],"graph"+data.id);break;case UI_GAUGE:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"WILL BE A GAUGE <input style='color:black;' id='gauge"+
data.id+
"' type='number' value='"+
data.value+
"' onchange='numberchange("+
data.id+
")' />"+
"</div>");}
break;case UI_ACCEL:if(hasAccel)break;var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
hasAccel=true;if(data.visible){parent.append("<div id='id"+
data.id+
"' "+style+" class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"ACCEL // Not implemented fully!<div class='accelerometer' id='accel"+
data.id+
"' ><div class='ball"+
data.id+
"'></div><pre class='accelerometeroutput"+
data.id+
"'></pre>"+
"</div>");requestOrientationPermission();}
break;case UPDATE_LABEL:$("#l"+data.id).html(data.value);break;case UPDATE_SWITCHER:switcher(data.id,data.value=="0"?0:1);break;case UPDATE_SLIDER:slider_move($("#id"+data.id),data.value,"100",false);break;case UPDATE_NUMBER:$("#num"+data.id).val(data.value);break;case UPDATE_TEXT_INPUT:$("#text"+data.id).val(data.value);break;case UPDATE_SELECT:$("#select"+data.id).val(data.value);break;case UPDATE_BUTTON:case UPDATE_PAD:case UPDATE_CPAD:break;case UPDATE_GAUGE:$("#gauge"+data.id).val(data.value);break;case UPDATE_ACCEL:break;default:console.error("Unknown type or event");break;}
if(data.type>=UPDATE_OFFSET&&data.type<UI_INITIAL_GUI){var element=$("#id"+data.id);if(data.type==UPDATE_SLIDER){element.removeClass("slider-turquoise slider-emerald slider-peterriver slider-wetasphalt slider-sunflower slider-carrot slider-alizarin");element.addClass("slider-"+colorClass(data.color));}else{element.removeClass("turquoise emerald peterriver wetasphalt sunflower carrot alizarin");element.addClass(colorClass(data.color));}}
$(".range-slider__range").each(function(){$(this)[0].value=$(this).attr("value");$(this).next().html($(this).attr("value"));});};websock.onmessage=handleEvent;}
function sliderchange(number){var val=$("#sl"+number).val();websock.send("slvalue:"+val+":"+number);}
function numberchange(number){var val=$("#num"+number).val();websock.send("nvalue:"+val+":"+number);}
function textchange(number){var val=$("#text"+number).val();websock.send("tvalue:"+val+":"+number);}
function tabclick(number){var val=$("#tab"+number).val();websock.send("tabvalue:"+val+":"+number);}
function selectchange(number){var val=$("#select"+number).val();websock.send("svalue:"+val+":"+number);}
function buttonclick(number,isdown){if(isdown)websock.send("bdown:"+number);else websock.send("bup:"+number);}
function padclick(type,number,isdown){switch(type){case CENTER:if(isdown)websock.send("pcdown:"+number);else websock.send("pcup:"+number);break;case UP:if(isdown)websock.send("pfdown:"+number);else websock.send("pfup:"+number);break;case DOWN:if(isdown)websock.send("pbdown:"+number);else websock.send("pbup:"+number);break;case LEFT:if(isdown)websock.send("pldown:"+number);else websock.send("plup:"+number);break;case RIGHT:if(isdown)websock.send("prdown:"+number);else websock.send("prup:"+number);break;}}
function switcher(number,state){if(state==null){if($("#s"+number).is(":checked")){websock.send("sactive:"+number);$("#sl"+number).addClass("checked");}else{websock.send("sinactive:"+number);$("#sl"+number).removeClass("checked");}}else if(state==1){$("#sl"+number).addClass("checked");$("#sl"+number).prop("checked",true);}else if(state==0){$("#sl"+number).removeClass("checked");$("#sl"+number).prop("checked",false);}}
var rangeSlider=function(isDiscrete){var range=$(".range-slider__range");var slidercb=function(){sliderchange($(this).attr("id").replace(/^\D+/g,""));};range.on({input:function(){$(this).next().html(this.value)}});range.each(function(){$(this).next().html(this.value);if($(this).attr("callbackSet")!="true"){if(!isDiscrete){$(this).on({input:slidercb});}else{$(this).on({change:slidercb});}
$(this).attr("callbackSet","true");}});};
)=====";

const uint8_t JS_CONTROLS_GZIP[3474] PROGMEM = { 31,139,8,0,86,185,205,97,2,255,237,91,235,115,218,72,18,255,238,191,66,86,182,130,116,198,60,146,56,155,5,203,41,130,73,194,45,49,62,131,55,91,151,205,185,6,105,48,170,8,73,43,141,140,189,44,255,251,245,188,164,145,16,152,216,187,123,143,202,151,4,245,244,227,55,221,61,239,182,29,248,49,209,46,251,87,253,179,254,184,223,25,92,189,187,236,91,207,26,141,182,45,27,46,122,131,97,231,20,104,77,73,59,63,237,140,123,87,195,183,111,71,189,177,213,84,121,199,253,113,111,96,41,132,115,144,44,200,49,82,166,172,127,213,165,148,103,121,166,46,231,122,150,113,189,185,28,143,135,103,214,243,60,159,160,54,27,207,51,206,65,231,13,128,120,145,103,228,196,102,227,69,198,55,250,216,31,119,223,247,46,172,163,60,107,74,111,54,142,20,238,65,255,20,104,47,11,188,156,218,108,188,204,56,207,46,63,188,1,218,247,121,78,65,109,54,190,87,220,213,251,121,12,142,63,191,28,91,175,242,220,74,75,179,241,42,147,120,119,209,57,127,111,253,32,8,157,211,83,78,185,58,31,246,207,40,171,104,232,14,122,157,11,193,220,108,252,160,88,236,188,177,154,133,128,112,154,18,144,81,111,208,235,130,182,66,76,36,185,169,68,101,120,62,238,83,255,23,194,34,201,77,37,44,31,250,64,40,68,133,209,154,74,76,62,116,126,182,154,133,120,48,90,83,13,197,184,119,110,53,139,145,96,196,166,18,135,119,157,203,119,61,171,89,136,131,160,54,149,48,116,186,93,154,27,89,8,198,140,83,144,21,5,105,102,159,14,63,158,165,121,61,232,189,29,167,249,123,209,127,247,126,156,102,105,183,119,54,134,160,203,14,118,175,198,151,23,255,184,28,246,71,189,84,85,247,170,247,161,119,209,25,100,227,164,123,117,222,3,169,139,254,79,32,250,44,37,126,236,141,59,163,243,247,157,129,162,254,106,116,121,246,118,48,252,152,179,209,237,92,92,12,199,105,86,119,175,58,131,254,63,59,23,224,234,151,41,233,180,115,241,99,154,161,221,171,179,225,89,207,122,118,116,212,190,65,145,118,29,161,112,118,138,8,178,124,188,208,58,81,132,238,12,147,181,204,80,220,177,109,236,89,83,228,197,152,145,98,207,117,112,212,13,124,226,250,73,144,196,162,105,154,248,54,113,3,95,179,3,47,136,186,30,138,99,131,253,236,59,230,82,252,176,206,146,249,4,71,41,189,29,47,92,98,207,20,62,20,99,213,103,173,8,147,36,242,117,248,231,215,36,112,99,172,183,5,139,112,161,100,192,115,28,33,207,73,155,51,127,74,142,16,19,28,69,238,13,142,82,166,204,191,146,105,129,9,138,195,25,242,72,202,148,250,91,242,196,137,63,245,130,133,162,135,187,95,182,219,40,138,130,76,94,134,66,54,35,207,253,13,69,174,159,50,208,72,200,70,7,69,95,244,182,131,167,40,241,136,36,234,237,213,106,143,122,126,129,39,113,96,127,105,43,191,33,12,62,182,9,118,138,81,136,240,175,9,142,201,48,114,177,79,16,37,157,227,104,238,198,49,252,50,204,229,106,47,229,140,209,13,126,39,19,0,154,188,192,70,222,136,4,17,186,198,181,24,147,62,193,115,67,199,113,152,184,44,79,98,189,250,247,209,240,172,22,19,232,197,181,59,189,51,210,244,49,205,182,162,56,2,251,65,164,232,118,33,194,44,131,192,162,195,210,45,103,235,186,212,86,166,188,237,78,141,84,116,223,242,19,207,51,151,153,46,6,42,68,81,140,51,46,179,205,125,152,153,252,228,58,159,1,36,39,127,250,92,196,139,34,2,46,248,206,112,2,59,153,131,231,204,26,114,28,67,255,155,110,214,130,233,20,6,197,119,134,254,36,10,22,240,61,35,115,207,208,117,179,45,66,81,179,189,0,108,67,82,115,45,170,106,24,117,35,136,66,18,247,32,55,34,176,176,33,124,84,123,202,11,54,34,60,15,110,48,31,76,58,27,37,135,215,17,198,190,110,174,177,2,206,28,95,132,157,18,46,14,154,161,208,234,218,89,160,9,4,20,228,211,39,175,94,62,63,106,151,72,101,93,207,81,125,99,105,123,174,253,165,37,60,87,93,229,58,61,67,190,227,225,159,220,216,157,184,158,75,238,186,64,184,6,7,45,33,142,251,69,7,60,125,186,47,125,94,155,185,142,131,125,115,153,6,132,14,128,44,95,69,144,82,118,232,121,239,6,126,12,220,152,96,31,166,23,253,38,181,105,51,155,122,181,28,75,149,121,157,37,214,194,245,157,96,81,163,9,73,173,212,194,32,34,251,150,174,255,254,123,121,203,171,198,166,150,23,47,158,167,241,101,243,233,71,60,25,193,111,76,12,125,17,183,234,117,253,160,40,56,11,98,226,163,57,62,208,91,235,141,84,235,129,94,95,128,203,219,43,12,120,31,172,92,232,216,147,9,27,248,65,136,125,75,122,214,192,55,132,78,213,126,28,120,24,228,175,65,37,231,212,40,223,14,57,183,41,55,9,190,5,124,105,172,179,49,147,229,63,137,18,220,94,181,51,104,108,52,237,130,141,49,130,202,226,24,203,105,195,148,182,69,27,37,148,105,224,107,32,205,29,150,98,247,105,160,236,78,97,50,130,134,154,195,230,34,218,138,173,52,111,39,129,115,199,104,54,124,225,8,146,141,175,175,228,206,195,244,3,178,146,202,213,96,13,30,46,252,243,8,130,16,145,59,163,226,250,158,235,227,17,101,171,152,48,3,50,254,138,148,171,28,48,33,133,233,160,162,107,21,8,187,88,108,89,51,185,11,177,88,110,243,39,129,86,201,4,71,73,4,77,98,31,221,148,145,193,11,48,238,136,218,36,161,23,247,10,128,182,184,123,40,229,3,180,140,78,85,71,129,23,215,166,65,212,67,0,30,123,152,250,206,58,97,11,9,44,147,183,60,46,75,202,222,42,172,75,130,217,172,174,218,74,12,141,84,10,2,108,182,39,17,70,95,218,210,19,252,232,211,42,142,161,8,123,1,114,140,34,55,59,252,180,210,128,18,151,64,4,24,112,15,77,176,199,60,52,71,174,255,30,35,232,158,116,80,198,80,212,199,142,44,45,218,51,72,29,208,152,250,145,127,118,185,55,204,37,255,180,68,0,244,131,18,30,49,85,40,156,44,168,224,88,169,147,77,146,30,150,218,106,40,132,65,14,107,221,177,227,222,104,174,99,85,92,71,63,224,97,112,157,131,61,189,162,233,7,44,199,14,116,24,115,48,234,173,10,89,4,116,187,151,204,253,88,131,109,143,163,17,158,202,192,185,167,108,3,69,40,225,219,164,122,78,160,85,63,158,29,157,72,245,204,23,148,86,7,226,241,44,170,115,142,56,68,62,3,226,21,112,8,235,76,76,99,255,30,46,96,151,80,73,21,222,32,47,193,76,33,213,193,181,213,161,91,39,204,1,121,159,243,243,228,127,175,211,69,103,97,10,251,19,93,61,73,8,9,184,179,39,196,223,16,246,61,61,240,231,48,56,49,12,13,31,24,153,12,219,0,24,57,137,170,70,39,115,147,10,166,34,73,184,85,128,175,195,101,1,228,66,39,105,248,168,83,25,68,33,206,183,33,36,72,236,25,219,24,180,178,25,218,92,226,90,24,97,58,210,79,249,142,154,14,96,5,132,80,81,101,112,219,171,42,211,2,225,120,136,14,177,147,88,241,61,80,62,197,228,245,194,255,208,200,254,115,211,141,143,92,138,36,222,48,182,249,90,69,173,25,89,66,88,150,222,212,95,235,16,35,216,240,56,176,87,210,21,171,180,111,66,216,245,43,39,199,174,31,38,68,163,235,156,85,97,18,147,224,182,194,109,22,76,6,126,151,134,82,26,165,27,200,92,118,178,131,70,101,39,44,117,153,168,172,207,172,155,249,217,39,53,33,243,38,211,184,158,55,244,74,172,37,63,232,239,111,43,3,231,128,141,136,52,36,118,8,66,52,17,238,246,220,147,99,164,229,166,171,16,57,124,196,94,158,87,181,242,249,74,153,171,182,113,139,201,138,121,34,156,230,61,113,242,244,201,15,47,143,26,237,227,58,130,84,0,24,247,194,97,215,71,95,131,168,92,32,7,42,122,44,40,122,193,245,53,152,74,249,115,144,188,199,66,162,23,112,95,3,169,148,63,7,105,178,11,164,58,79,169,108,215,108,89,98,100,190,214,1,107,150,133,83,55,154,87,54,96,231,151,130,213,221,193,11,129,173,240,237,2,252,225,143,20,185,156,137,142,235,48,72,242,115,15,29,234,52,95,31,184,114,170,67,226,161,43,103,153,14,117,229,100,16,189,199,67,100,249,248,104,144,57,45,107,48,163,199,195,228,67,249,209,56,243,106,214,128,78,30,15,148,13,166,71,227,204,105,89,131,105,63,30,166,24,54,143,6,90,208,179,117,111,199,158,131,254,31,86,102,250,113,200,15,226,127,204,42,173,236,200,34,122,219,38,148,11,121,190,63,43,221,3,242,77,27,147,169,104,115,23,102,210,6,252,143,110,173,74,179,1,191,248,254,171,82,60,43,84,202,140,93,93,113,53,202,137,178,148,139,41,217,229,0,169,78,168,76,197,136,105,48,246,215,174,58,214,82,133,191,7,126,219,196,213,213,4,16,183,87,76,188,53,241,144,253,165,205,215,55,63,153,151,166,133,207,158,144,182,100,1,156,204,216,229,174,100,229,95,249,61,61,172,161,245,237,215,2,217,115,236,183,128,237,22,48,122,201,91,0,184,67,140,168,212,3,35,212,121,211,90,243,93,254,170,50,117,97,110,99,73,119,90,192,35,47,34,164,77,106,114,22,225,169,85,81,130,72,233,212,65,10,126,61,219,32,150,221,129,174,133,173,168,44,237,16,149,163,153,80,203,43,128,175,9,118,186,252,219,88,122,65,16,182,232,74,182,50,217,53,178,161,163,208,229,150,17,112,79,93,15,2,108,164,43,27,125,53,97,47,94,223,25,100,230,198,128,135,16,56,208,210,142,233,166,5,167,214,39,172,223,135,36,56,228,103,81,189,189,98,235,173,206,232,122,85,93,35,105,230,3,28,43,140,130,121,72,12,125,140,38,26,9,52,113,56,135,95,6,31,98,90,16,65,87,205,215,252,230,119,159,246,167,198,153,64,194,128,79,211,92,34,15,71,84,197,12,17,170,83,115,2,28,107,126,64,52,124,235,198,68,107,253,242,11,139,113,201,178,92,182,234,178,194,132,111,35,83,222,148,98,15,219,91,134,38,111,95,187,246,144,99,144,55,63,108,20,242,186,143,214,6,247,103,1,98,142,149,56,202,162,80,244,109,16,178,215,62,10,159,255,220,232,226,141,179,140,164,112,179,152,202,149,120,146,107,47,235,219,135,254,174,29,163,9,176,206,6,216,216,156,201,135,133,232,96,236,254,134,13,51,203,37,54,60,97,147,163,231,175,130,214,176,116,126,254,171,176,160,219,123,176,208,194,155,191,8,76,76,112,120,15,26,86,243,244,109,42,16,227,116,234,94,39,17,102,80,88,229,68,225,146,64,242,216,72,100,253,154,182,124,35,39,128,198,252,44,144,22,101,124,18,202,63,91,107,213,30,242,48,215,6,71,193,206,152,53,140,110,174,141,117,217,170,46,160,166,34,185,24,23,106,222,88,168,73,108,125,64,100,86,139,130,4,220,79,31,194,65,35,164,15,45,34,25,187,115,248,85,135,179,66,163,12,105,45,76,226,153,177,188,109,145,184,122,215,202,82,11,150,153,66,41,204,67,144,43,184,149,146,188,86,137,195,62,125,254,131,237,201,2,184,111,99,129,143,133,143,253,193,64,123,211,211,58,26,115,139,118,223,6,246,26,37,215,248,63,121,230,96,229,135,116,98,149,85,119,38,111,255,147,227,153,214,248,177,26,140,255,149,232,50,103,105,117,90,196,68,52,119,30,242,183,126,236,104,211,196,243,238,246,213,219,7,68,123,135,97,15,75,75,0,121,172,25,169,128,255,68,149,153,32,175,120,101,205,227,118,12,251,211,82,197,65,66,232,146,86,148,9,139,115,231,246,202,188,66,82,40,165,204,172,50,67,189,27,205,138,9,196,210,184,46,152,190,60,110,121,119,130,51,65,67,127,221,104,53,75,21,240,235,45,113,77,66,139,209,140,220,178,14,56,20,85,85,29,38,93,93,222,151,173,107,19,55,32,84,3,59,222,167,93,1,233,123,122,162,156,199,89,150,179,195,230,87,200,139,19,195,218,46,116,55,105,81,36,160,146,178,183,185,172,126,189,181,46,201,103,100,106,86,76,47,95,97,149,207,7,156,46,107,66,101,201,17,43,104,50,244,75,255,139,31,44,124,54,79,209,83,24,59,58,233,82,89,54,87,211,246,19,43,87,199,255,244,105,218,114,156,175,1,226,187,56,89,106,83,140,119,91,213,105,89,185,68,49,151,66,42,95,185,200,211,231,48,173,226,21,53,196,135,162,106,87,126,102,37,186,146,146,213,227,74,74,90,125,43,9,188,220,86,126,165,213,181,102,91,34,201,138,212,4,143,126,80,62,249,200,41,178,180,11,25,118,9,90,65,171,194,76,241,9,96,219,16,109,196,177,218,163,247,2,37,23,153,112,226,199,180,14,74,57,239,139,131,254,167,198,103,49,158,243,39,127,70,99,247,5,156,234,211,90,60,49,121,148,114,242,3,183,82,59,55,199,113,140,96,109,83,106,168,212,50,79,142,79,172,120,124,249,227,9,4,250,248,169,15,38,45,65,103,73,159,85,204,198,108,69,137,61,102,185,165,31,192,255,172,4,82,112,171,86,114,235,106,153,21,54,161,108,51,227,239,96,69,185,141,42,179,193,103,157,109,70,200,46,70,228,221,83,169,9,186,124,111,181,128,38,59,216,200,29,233,75,131,34,38,193,173,129,217,193,144,90,11,195,155,171,110,76,159,63,89,153,175,248,153,87,59,161,52,69,27,29,116,90,129,37,9,203,205,165,79,52,116,242,169,22,12,138,2,71,165,182,145,63,228,180,54,33,9,237,251,161,132,118,14,75,110,150,222,172,120,186,131,226,233,38,197,244,157,108,179,234,29,220,23,78,54,169,166,79,154,155,85,123,59,168,246,54,169,102,175,144,155,117,71,59,232,142,74,116,231,74,191,229,46,70,4,62,134,253,19,102,137,198,126,89,226,111,2,224,155,165,120,150,221,46,204,224,45,89,171,99,166,229,217,50,207,17,168,191,193,138,233,226,180,165,20,58,75,37,249,90,108,169,201,245,239,213,149,175,233,207,212,49,125,90,214,151,38,191,205,190,15,70,145,39,140,130,48,107,151,111,160,5,221,141,117,221,27,96,221,163,94,62,141,242,63,80,81,30,196,178,74,105,55,62,117,99,59,194,68,92,40,51,38,107,227,250,166,252,141,145,61,177,148,117,46,183,206,228,87,46,216,158,208,14,132,112,152,195,70,253,95,191,156,30,212,175,171,58,91,202,248,35,29,123,80,102,199,191,214,250,202,153,91,18,41,69,236,200,86,43,241,196,183,105,201,221,36,216,102,9,168,2,180,225,52,49,129,147,230,8,195,230,108,223,210,105,84,116,254,135,16,170,123,164,80,134,86,58,98,37,243,77,101,225,190,200,241,236,109,182,91,21,86,219,43,182,190,255,27,5,224,136,21,7,58,0,0 };
