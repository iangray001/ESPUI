const char JS_CONTROLS[] PROGMEM = R"=====(
const UI_INITIAL_GUI=200;const UI_RELOAD=201;const UPDATE_OFFSET=100;const UI_EXTEND_GUI=210;const UI_TITEL=0;const UI_PAD=1;const UPDATE_PAD=101;const UI_CPAD=2;const UPDATE_CPAD=102;const UI_BUTTON=3;const UPDATE_BUTTON=103;const UI_LABEL=4;const UPDATE_LABEL=104;const UI_SWITCHER=5;const UPDATE_SWITCHER=105;const UI_SLIDER=6;const UPDATE_SLIDER=106;const UI_NUMBER=7;const UPDATE_NUMBER=107;const UI_TEXT_INPUT=8;const UPDATE_TEXT_INPUT=108;const UI_TAB=11;const UPDATE_TAB=111;const UI_SELECT=12;const UPDATE_SELECT=112;const UI_OPTION=13;const UPDATE_OPTION=113;const UI_MIN=14;const UPDATE_MIN=114;const UI_MAX=15;const UPDATE_MAX=115;const UI_STEP=16;const UPDATE_STEP=116;const UI_GAUGE=17;const UPDATE_GAUGE=117;const UI_ACCEL=18;const UPDATE_ACCEL=118;const UI_SEPARATOR=19;const UPDATE_SEPARATOR=119;const UI_TIME=20;const UPDATE_TIME=120;const UI_CHART=21;const UP=0;const DOWN=1;const LEFT=2;const RIGHT=3;const CENTER=4;const C_TURQUOISE=0;const C_EMERALD=1;const C_PETERRIVER=2;const C_WETASPHALT=3;const C_SUNFLOWER=4;const C_CARROT=5;const C_ALIZARIN=6;const C_DARK=7;const C_NONE=255;var hasAccel=false;var sliderContinuous=false;function colorClass(colorId){colorId=Number(colorId);switch(colorId){case C_TURQUOISE:return"turquoise";case C_EMERALD:return"emerald";case C_PETERRIVER:return"peterriver";case C_WETASPHALT:return"wetasphalt";case C_SUNFLOWER:return"sunflower";case C_CARROT:return"carrot";case C_ALIZARIN:return"alizarin";case C_DARK:case C_NONE:return"dark";default:return"";}}
var websock;var websockConnected=false;var charts={}
function requestOrientationPermission(){}
function restart(){charts={}
$(document).add("*").off();$("#row").html("");websock.close();start();}
function conStatusError(){websockConnected=false;$("#conStatus").removeClass("color-green");$("#conStatus").addClass("color-red");$("#conStatus").html("Error / No Connection &#8635;");$("#conStatus").off();$("#conStatus").on({click:restart,});}
function handleVisibilityChange(){if(!websockConnected&&!document.hidden){restart();}}
function start(){document.addEventListener("visibilitychange",handleVisibilityChange,false);if(window.location.port!=""||window.location.port!=80||window.location.port!=443){websock=new WebSocket("ws://"+window.location.hostname+":"+window.location.port+"/ws");}else{websock=new WebSocket("ws://"+window.location.hostname+"/ws");}
websock.onopen=function(evt){console.log("websock open");$("#conStatus").addClass("color-green");$("#conStatus").text("Connected");websockConnected=true;};websock.onclose=function(evt){console.log("websock close");conStatusError();};websock.onerror=function(evt){console.log(evt);conStatusError();};var handleEvent=function(evt){console.log(evt);var data=JSON.parse(evt.data);var e=document.body;var center="";switch(data.type){case UI_INITIAL_GUI:$("#row").html("");$("#tabsnav").html("");$("#tabscontent").html("");if(data.sliderContinuous){sliderContinuous=data.sliderContinuous;}
data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element),};handleEvent(fauxEvent);});if(data.totalcontrols>(data.controls.length-1)){websock.send("uiok:"+(data.controls.length-1));}
break;case UI_EXTEND_GUI:data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element),};handleEvent(fauxEvent);});if(data.totalcontrols>data.startindex+(data.controls.length-1)){websock.send("uiok:"+(data.startindex+(data.controls.length-1)));}
break;case UI_RELOAD:window.location.reload();break;case UI_TITEL:document.title=data.label;$("#mainHeader").html(data.label);break;case UI_LABEL:case UI_NUMBER:case UI_TEXT_INPUT:case UI_SELECT:case UI_GAUGE:case UI_SEPARATOR:if(data.visible)addToHTML(data);break;case UI_BUTTON:if(data.visible){addToHTML(data);$("#btn"+data.id).on({touchstart:function(e){e.preventDefault();buttonclick(data.id,true);},touchend:function(e){e.preventDefault();buttonclick(data.id,false);},});}
break;case UI_SWITCHER:if(data.visible){addToHTML(data);switcher(data.id,data.value);}
break;case UI_CPAD:case UI_PAD:if(data.visible){addToHTML(data);$("#pf"+data.id).on({touchstart:function(e){e.preventDefault();padclick(UP,data.id,true);},touchend:function(e){e.preventDefault();padclick(UP,data.id,false);},});$("#pl"+data.id).on({touchstart:function(e){e.preventDefault();padclick(LEFT,data.id,true);},touchend:function(e){e.preventDefault();padclick(LEFT,data.id,false);},});$("#pr"+data.id).on({touchstart:function(e){e.preventDefault();padclick(RIGHT,data.id,true);},touchend:function(e){e.preventDefault();padclick(RIGHT,data.id,false);},});$("#pb"+data.id).on({touchstart:function(e){e.preventDefault();padclick(DOWN,data.id,true);},touchend:function(e){e.preventDefault();padclick(DOWN,data.id,false);},});$("#pc"+data.id).on({touchstart:function(e){e.preventDefault();padclick(CENTER,data.id,true);},touchend:function(e){e.preventDefault();padclick(CENTER,data.id,false);},});}
break;case UI_SLIDER:if(data.visible){addToHTML(data);rangeSlider(!sliderContinuous);}
break;case UI_CHART:if(data.visible){addToHTML(data);var ct=JSON.parse(data.value);var chartData=ct.hasOwnProperty('data')?ct.data:"{}";var chartType=ct.hasOwnProperty('type')?ct.type:"line";var chartOptions=ct.hasOwnProperty('options')?ct.options:"{}";const initFn={"line":Chartist.Line,"bar":Chartist.Bar,"pie":Chartist.Pie};charts['ch'+data.id]=new initFn[chartType]('#ch'+data.id,chartData,chartOptions);}
break;case UI_TAB:if(data.visible){$("#tabsnav").append("<li><a onmouseup='tabclick("+data.id+")' href='#tab"+data.id+"'>"+data.value+"</a></li>");$("#tabscontent").append("<div id='tab"+data.id+"'></div>");tabs=$(".tabscontent").tabbedContent({loop:true}).data("api");$("a").filter(function(){return $(this).attr("href")==="#click-to-switch";}).on("click",function(e){var tab=prompt("Tab to switch to (number or id)?");if(!tabs.switchTab(tab)){alert("That tab does not exist :\\");}
e.preventDefault();});}
break;case UI_OPTION:if(data.parentControl){var parent=$("#select"+data.parentControl);parent.append("<option id='option"+
data.id+
"' value='"+
data.value+
"' "+
data.selected+
">"+
data.label+
"</option>");}
break;case UI_MIN:if(data.parentControl){if($('#sl'+data.parentControl).length){$('#sl'+data.parentControl).attr("min",data.value);}else if($('#num'+data.parentControl).length){$('#num'+data.parentControl).attr("min",data.value);}}
break;case UI_MAX:if(data.parentControl){if($('#sl'+data.parentControl).length){$('#sl'+data.parentControl).attr("max",data.value);}else if($('#text'+data.parentControl).length){$('#text'+data.parentControl).attr("maxlength",data.value);}else if($('#num'+data.parentControl).length){$('#num'+data.parentControl).attr("max",data.value);}}
break;case UI_STEP:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){parent.attr("step",data.value);}}
break;case UI_ACCEL:if(hasAccel)break;hasAccel=true;if(data.visible){addToHTML(data);requestOrientationPermission();}
break;case UPDATE_LABEL:$("#l"+data.id).html(data.value);if(data.hasOwnProperty('elementStyle')){$("#l"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_SWITCHER:switcher(data.id,data.value=="0"?0:1);if(data.hasOwnProperty('elementStyle')){$("#sl"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_SLIDER:$("#sl"+data.id).attr("value",data.value)
slider_move($("#sl"+data.id).parent().parent(),data.value,"100",false);if(data.hasOwnProperty('elementStyle')){$("#sl"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_NUMBER:$("#num"+data.id).val(data.value);if(data.hasOwnProperty('elementStyle')){$("#num"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_TEXT_INPUT:$("#text"+data.id).val(data.value);if(data.hasOwnProperty('elementStyle')){$("#text"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_SELECT:$("#select"+data.id).val(data.value);if(data.hasOwnProperty('elementStyle')){$("#select"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_BUTTON:$("#btn"+data.id).val(data.value);$("#btn"+data.id).text(data.value);if(data.hasOwnProperty('elementStyle')){$("#btn"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_PAD:case UPDATE_CPAD:break;case UPDATE_GAUGE:$("#gauge"+data.id).val(data.value);if(data.hasOwnProperty('elementStyle')){$("#gauge"+data.id).attr("style",data.elementStyle);}
break;case UPDATE_ACCEL:break;case UPDATE_TIME:var rv=new Date().toISOString();websock.send("time:"+rv+":"+data.id);break;default:console.error("Unknown type or event");break;}
if(data.type>=UI_TITEL&&data.type<UPDATE_OFFSET){processEnabled(data);}
if(data.type>=UPDATE_OFFSET&&data.type<UI_INITIAL_GUI){var element=$("#id"+data.id);if(data.hasOwnProperty('panelStyle')){$("#id"+data.id).attr("style",data.panelStyle);}
if(data.hasOwnProperty('visible')){if(data['visible'])
$("#id"+data.id).show();else
$("#id"+data.id).hide();}
if(data.type==UPDATE_SLIDER){element.removeClass("slider-turquoise slider-emerald slider-peterriver slider-wetasphalt slider-sunflower slider-carrot slider-alizarin");element.addClass("slider-"+colorClass(data.color));}else{element.removeClass("turquoise emerald peterriver wetasphalt sunflower carrot alizarin");element.addClass(colorClass(data.color));}
processEnabled(data);}
$(".range-slider__range").each(function(){$(this)[0].value=$(this).attr("value");$(this).next().html($(this).attr("value"));});};websock.onmessage=handleEvent;}
function sliderchange(number){var val=$("#sl"+number).val();websock.send("slvalue:"+val+":"+number);$(".range-slider__range").each(function(){$(this).attr("value",$(this)[0].value);});}
function numberchange(number){var val=$("#num"+number).val();websock.send("nvalue:"+val+":"+number);}
function textchange(number){var val=$("#text"+number).val();websock.send("tvalue:"+val+":"+number);}
function tabclick(number){var val=$("#tab"+number).val();websock.send("tabvalue:"+val+":"+number);}
function selectchange(number){var val=$("#select"+number).val();websock.send("svalue:"+val+":"+number);}
function buttonclick(number,isdown){if(isdown)websock.send("bdown:"+number);else websock.send("bup:"+number);}
function padclick(type,number,isdown){if($("#id"+number+" nav").hasClass("disabled")){return;}
switch(type){case CENTER:if(isdown)websock.send("pcdown:"+number);else websock.send("pcup:"+number);break;case UP:if(isdown)websock.send("pfdown:"+number);else websock.send("pfup:"+number);break;case DOWN:if(isdown)websock.send("pbdown:"+number);else websock.send("pbup:"+number);break;case LEFT:if(isdown)websock.send("pldown:"+number);else websock.send("plup:"+number);break;case RIGHT:if(isdown)websock.send("prdown:"+number);else websock.send("prup:"+number);break;}}
function switcher(number,state){if(state==null){if(!$("#sl"+number).hasClass("checked")){websock.send("sactive:"+number);$("#sl"+number).addClass("checked");}else{websock.send("sinactive:"+number);$("#sl"+number).removeClass("checked");}}else if(state==1){$("#sl"+number).addClass("checked");$("#sl"+number).prop("checked",true);}else if(state==0){$("#sl"+number).removeClass("checked");$("#sl"+number).prop("checked",false);}}
var rangeSlider=function(isDiscrete){var range=$(".range-slider__range");var slidercb=function(){sliderchange($(this).attr("id").replace(/^\D+/g,""));};range.on({input:function(){$(this).next().html(this.value)}});range.each(function(){$(this).next().html(this.value);if($(this).attr("callbackSet")!="true"){if(!isDiscrete){$(this).on({input:slidercb});}else{$(this).on({change:slidercb});}
$(this).attr("callbackSet","true");}});};var addToHTML=function(data){panelStyle=data.hasOwnProperty('panelStyle')?" style='"+data.panelStyle+"' ":"";panelwide=data.hasOwnProperty('wide')?"wide":"";if(!data.hasOwnProperty('parentControl')||$("#tab"+data.parentControl).length>0){var parent=data.hasOwnProperty('parentControl')?$("#tab"+data.parentControl):$("#row");var html="";switch(data.type){case UI_LABEL:case UI_BUTTON:case UI_SWITCHER:case UI_CPAD:case UI_PAD:case UI_SLIDER:case UI_NUMBER:case UI_TEXT_INPUT:case UI_SELECT:case UI_GAUGE:case UI_ACCEL:case UI_CHART:html="<div id='id"+data.id+"' "+panelStyle+" class='two columns "+panelwide+" card tcenter "+
colorClass(data.color)+"'><h5>"+data.label+"</h5><hr/>"+
elementHTML(data)+
"</div>";break;case UI_SEPARATOR:html="<div id='id"+data.id+"' "+panelStyle+" class='sectionbreak columns'>"+
"<h5>"+data.label+"</h5><hr/></div>";break;case UI_TIME:break;}
parent.append(html);}else{var parent=$("#id"+data.parentControl);parent.append(elementHTML(data));}}
var elementHTML=function(data){var id=data.id
var elementStyle=data.hasOwnProperty('elementStyle')?" style='"+data.elementStyle+"' ":"";switch(data.type){case UI_LABEL:return"<span id='l"+id+"' "+elementStyle+
" class='label label-wrap'>"+data.value+"</span>";case UI_BUTTON:return"<button id='btn"+id+"' "+elementStyle+
" onmousedown='buttonclick("+id+", true)'"+
" onmouseup='buttonclick("+id+", false)'>"+
data.value+"</button>";case UI_SWITCHER:return"<label id='sl"+id+"' "+elementStyle+
" class='switch "+(data.value=="1"?"checked":"")+
(data.hasOwnProperty('vertical')?" vert-switcher ":"")+
"'>"+
"<div class='in'>"+
"<input type='checkbox' id='s"+id+"' onClick='switcher("+id+",null)' "+
(data.value=="1"?"checked":"")+"/></div></label>";case UI_CPAD:case UI_PAD:return"<nav class='control'><ul>"+
"<li><a onmousedown='padclick(UP, "+id+", true)' "+
"onmouseup='padclick(UP, "+id+", false)' id='pf"+id+"'>&#9650;</a></li>"+
"<li><a onmousedown='padclick(RIGHT, "+id+", true)' "+
"onmouseup='padclick(RIGHT, "+id+", false)' id='pr"+id+"'>&#9650;</a></li>"+
"<li><a onmousedown='padclick(LEFT, "+id+", true)' "+
"onmouseup='padclick(LEFT, "+id+", false)' id='pl"+id+"'>&#9650;</a></li>"+
"<li><a onmousedown='padclick(DOWN, "+id+", true)' "+
"onmouseup='padclick(DOWN, "+id+", false)' id='pb"+id+"'>&#9650;</a></li>"+
"</ul>"+
(data.type==UI_CPAD?"<a class='confirm' onmousedown='padclick(CENTER,"+id+", true)' "+
"onmouseup='padclick(CENTER, "+id+", false)' id='pc"+id+"'>OK</a>":"")+
"</nav>";case UI_SLIDER:return"<div class='range-slider "+
(data.hasOwnProperty('vertical')?" vert-slider ":"")+
"'>"+
"<input id='sl"+id+"' type='range' min='0' max='100' value='"+data.value+"' "+
elementStyle+" class='range-slider__range'><span class='range-slider__value'>"+
data.value+"</span></div>";case UI_NUMBER:return"<input style='color:black;' "+elementStyle+" id='num"+id+
"' type='number' value='"+data.value+"' onchange='numberchange("+id+")' />";case UI_TEXT_INPUT:return"<input style='color:black;' "+elementStyle+" id='text"+id+
"' value='"+data.value+"' onchange='textchange("+id+")' />";case UI_SELECT:return"<select style='color:black;' "+elementStyle+" id='select"+id+
"' onchange='selectchange("+id+")' />";case UI_GAUGE:return"WILL BE A GAUGE <input style='color:black;' id='gauge"+id+
"' type='number' value='"+data.value+"' onchange='numberchange("+id+")' />";case UI_ACCEL:return"ACCEL // Not implemented fully!<div class='accelerometer' id='accel"+id+
"' ><div class='ball"+id+"'></div><pre class='accelerometeroutput"+id+"'></pre>";case UI_CHART:return"<div class='ct-chart' id='ch"+id+"'></div>";default:return"";}}
var processEnabled=function(data){switch(data.type){case UI_SWITCHER:case UPDATE_SWITCHER:if(data.enabled){$("#sl"+data.id).removeClass('disabled');$("#s"+data.id).prop("disabled",false);}else{$("#sl"+data.id).addClass('disabled');$("#s"+data.id).prop("disabled",true);}
break;case UI_SLIDER:case UPDATE_SLIDER:$("#sl"+data.id).prop("disabled",!data.enabled);break;case UI_NUMBER:case UPDATE_NUMBER:$("#num"+data.id).prop("disabled",!data.enabled);break;case UI_TEXT_INPUT:case UPDATE_TEXT_INPUT:$("#text"+data.id).prop("disabled",!data.enabled);break;case UI_SELECT:case UPDATE_SELECT:$("#select"+data.id).prop("disabled",!data.enabled);break;case UI_BUTTON:case UPDATE_BUTTON:$("#btn"+data.id).prop("disabled",!data.enabled);break;case UI_PAD:case UI_CPAD:case UPDATE_PAD:case UPDATE_CPAD:if(data.enabled){$("#id"+data.id+" nav").removeClass('disabled');}else{$("#id"+data.id+" nav").addClass('disabled');}
break;}}
)=====";

const uint8_t JS_CONTROLS_GZIP[4072] PROGMEM = { 31,139,8,0,128,250,70,98,2,255,197,27,105,119,218,72,242,187,127,133,172,228,5,177,198,28,185,38,3,150,253,8,38,9,59,216,120,109,60,153,183,153,172,159,144,26,163,103,33,105,36,97,146,113,248,239,91,125,170,91,7,96,60,179,251,37,70,213,213,213,213,213,85,93,87,199,14,252,56,209,174,7,55,131,243,193,120,208,29,222,124,188,30,152,47,155,205,142,205,7,46,251,195,81,247,20,96,45,14,187,56,237,142,251,55,163,15,31,174,250,99,179,37,227,246,127,27,247,207,79,41,141,150,4,31,15,198,253,161,41,1,46,128,98,134,30,1,165,139,12,110,122,24,242,82,69,234,81,172,151,41,214,251,235,241,120,116,110,190,82,241,24,180,213,124,149,98,14,187,239,129,137,215,42,34,5,182,154,175,83,188,171,207,131,113,239,83,255,210,124,163,162,10,120,171,249,70,194,30,14,78,1,246,54,131,75,161,173,230,219,20,243,252,250,236,61,192,126,82,49,25,180,213,252,73,18,23,200,17,14,228,226,122,108,190,83,177,165,145,86,243,157,52,163,251,222,108,101,4,74,97,146,64,175,250,195,126,15,38,102,100,202,193,45,73,170,163,139,241,0,203,47,35,86,14,110,73,98,61,27,0,32,35,85,2,107,73,50,61,235,254,102,182,50,242,36,176,150,44,202,113,255,194,108,101,37,73,128,45,73,142,31,187,215,31,251,102,43,35,71,6,109,73,98,236,246,122,248,108,51,34,100,208,214,59,89,48,23,221,203,238,120,4,199,240,115,86,54,98,36,29,194,250,124,214,7,139,200,200,27,3,91,47,37,45,239,125,234,94,142,193,18,4,158,48,129,211,209,231,115,97,0,195,254,135,177,80,244,203,193,199,79,99,161,206,189,254,249,24,180,131,75,178,119,51,190,190,252,215,245,104,112,213,23,164,122,55,253,179,254,101,119,152,26,84,239,230,162,15,179,46,7,191,194,212,151,2,248,185,63,238,94,93,124,234,14,37,242,55,87,215,231,31,134,163,207,202,26,189,238,229,229,104,44,212,191,119,211,29,14,254,221,189,132,51,125,43,64,167,221,203,95,132,42,247,110,206,71,231,32,144,55,111,58,247,86,164,205,172,184,107,219,200,51,167,150,23,35,2,138,61,215,65,81,47,240,19,215,95,4,139,152,13,77,23,190,157,184,129,175,217,129,23,68,61,207,138,99,131,252,28,56,213,7,246,195,60,95,204,39,40,18,240,78,188,116,19,123,38,225,89,49,146,37,211,142,80,178,136,124,29,254,249,99,17,184,49,210,59,12,133,9,138,35,160,57,138,44,207,17,195,169,212,56,70,136,18,20,69,238,61,138,4,82,42,69,142,180,68,137,21,135,51,203,75,4,146,144,42,199,137,23,254,212,11,150,18,29,42,100,62,110,91,81,20,164,243,185,192,249,176,229,185,127,90,145,235,11,4,44,254,54,251,141,101,207,17,29,43,186,211,59,14,154,90,11,47,225,64,189,179,90,237,225,83,88,162,73,28,216,119,29,233,55,28,137,143,236,4,57,210,97,217,51,43,74,98,243,97,181,39,206,39,66,127,44,80,156,140,34,23,249,137,133,65,23,40,154,187,113,12,191,140,170,138,25,39,48,29,128,41,153,231,134,19,216,139,57,76,173,214,45,199,49,244,127,232,213,122,48,157,26,213,206,115,67,127,22,5,75,248,158,37,115,207,208,245,106,135,113,86,183,189,32,70,128,194,232,117,164,69,64,237,174,128,141,69,220,7,177,69,176,86,201,110,48,117,129,11,107,68,104,30,220,35,170,103,58,81,160,195,219,8,33,95,175,230,80,129,79,5,47,66,78,1,22,101,154,112,161,53,180,243,64,99,28,96,38,95,60,123,247,246,213,155,78,193,172,116,235,10,212,55,30,108,207,181,239,218,76,134,181,149,178,233,153,229,59,30,250,213,141,221,137,235,185,201,247,30,0,110,65,64,15,238,212,216,207,10,224,197,139,125,46,243,250,204,117,28,228,87,31,196,209,96,125,16,100,249,113,9,116,216,121,255,30,126,12,221,56,65,62,88,158,126,47,214,180,201,154,122,173,152,151,26,145,122,181,3,12,45,93,223,9,150,117,47,176,137,182,212,195,32,74,246,77,93,255,241,163,120,228,93,179,108,228,245,235,87,226,124,77,31,45,181,207,104,114,5,191,81,98,232,203,184,221,104,232,7,217,137,179,32,78,124,107,142,14,244,118,126,16,83,61,208,27,75,16,121,103,133,128,223,157,137,51,26,123,92,97,3,63,8,145,111,114,201,26,232,62,193,183,152,31,7,30,130,249,183,64,146,98,106,24,111,11,157,43,211,205,4,125,3,254,196,89,167,54,147,234,127,18,45,80,103,213,73,89,35,214,180,13,111,4,17,72,102,109,76,161,134,48,108,13,53,12,40,162,64,221,3,214,29,162,98,155,40,96,116,199,74,44,243,159,87,163,243,122,104,69,112,33,192,64,29,195,232,40,50,133,222,78,2,231,59,189,191,224,11,69,160,108,220,85,96,244,122,242,61,68,204,89,168,225,110,187,224,14,194,160,196,154,196,190,117,95,4,6,70,193,52,18,121,8,116,158,44,147,245,116,213,135,156,239,43,196,3,61,34,112,76,58,10,188,184,62,13,162,190,5,204,35,15,225,237,153,199,15,120,111,112,177,127,163,162,123,192,232,109,34,152,56,1,223,112,235,78,191,115,228,106,109,213,145,196,108,136,89,112,6,41,171,73,144,88,30,95,239,216,80,151,247,144,127,155,204,14,91,85,97,124,245,24,249,112,119,47,220,224,14,204,170,20,29,54,50,137,144,117,215,225,162,78,147,130,246,255,119,135,84,238,248,186,3,147,70,223,14,118,218,241,54,243,243,50,160,73,84,59,123,151,68,200,11,44,7,44,67,197,38,233,82,91,40,118,226,38,30,162,90,227,89,19,228,17,53,156,91,174,255,9,89,160,67,92,11,83,132,44,61,146,228,180,249,23,205,56,196,103,154,82,8,16,205,8,196,39,9,173,165,65,22,18,183,185,148,137,123,240,80,21,174,175,113,240,105,124,54,52,168,125,170,76,208,148,44,55,233,33,59,11,111,110,146,248,250,1,65,115,29,234,24,147,96,97,207,136,236,219,233,157,81,125,64,245,48,66,248,216,79,105,200,131,69,185,72,18,124,221,129,35,53,24,137,26,190,13,225,80,106,132,10,156,233,46,52,152,111,91,81,175,172,238,141,167,134,155,119,71,111,36,112,170,156,44,69,183,60,194,96,134,44,206,118,133,220,241,239,173,132,23,78,119,150,93,104,57,116,211,215,23,181,93,101,87,68,67,150,29,97,209,123,58,139,56,107,122,58,147,10,149,28,155,209,211,217,36,249,220,211,249,84,201,228,24,157,60,157,81,156,146,62,157,79,133,74,142,77,251,233,108,210,140,248,233,140,102,232,172,181,110,82,204,217,108,124,17,142,129,175,136,95,55,246,115,113,64,222,186,113,117,96,51,85,18,209,36,114,4,36,95,25,34,95,59,197,97,146,13,193,190,21,143,150,254,69,4,33,102,148,124,55,42,24,185,82,61,177,105,208,212,214,31,86,122,58,105,12,49,81,209,36,28,43,209,73,248,87,91,247,92,31,73,211,70,33,150,112,92,52,51,160,67,116,50,251,160,139,210,82,129,235,187,201,7,223,124,160,36,219,61,76,14,242,140,250,16,62,107,250,196,138,36,216,123,43,170,233,161,43,163,93,184,104,213,161,137,229,151,138,61,171,112,117,250,74,130,119,74,252,139,216,218,87,163,242,76,66,170,9,65,213,228,109,228,79,102,220,125,159,63,23,53,36,180,194,144,196,6,71,158,123,124,100,105,129,63,135,51,70,139,208,172,0,14,213,48,161,235,7,122,181,162,205,34,52,53,43,152,130,4,175,28,179,15,114,154,7,250,81,195,58,62,106,0,201,194,88,83,172,233,184,247,154,235,144,165,20,98,71,13,24,193,115,241,60,19,8,212,85,2,240,53,65,78,143,126,27,15,94,16,132,109,108,64,171,42,81,14,67,183,66,151,174,108,1,246,212,245,32,140,54,132,65,225,4,18,215,19,180,231,70,50,115,99,224,39,73,32,57,196,27,211,171,166,105,66,142,130,247,125,152,4,135,212,203,233,16,138,97,51,215,9,92,175,201,166,137,117,9,216,49,195,40,152,135,144,204,140,173,137,150,4,26,157,136,127,25,62,41,251,104,144,88,195,109,113,66,35,236,125,188,159,58,69,130,25,6,124,66,180,102,121,160,123,64,98,102,37,152,166,230,4,40,214,252,32,209,208,55,208,25,173,253,251,239,36,77,43,184,13,10,140,157,150,56,197,241,131,197,193,140,30,141,241,40,219,20,132,197,251,44,134,104,212,78,216,25,168,168,29,250,153,30,26,53,6,114,110,244,167,126,176,199,207,110,79,175,104,68,5,204,10,135,82,141,192,3,28,66,23,67,24,251,152,195,72,184,7,128,163,6,165,121,172,231,119,116,54,40,221,14,128,159,131,141,196,94,165,104,11,44,162,197,170,95,142,67,149,96,238,250,186,26,202,224,204,90,99,244,225,40,55,47,80,138,84,182,66,110,159,221,223,254,254,125,90,223,214,236,19,231,229,155,87,40,199,18,107,80,244,191,91,162,185,189,228,28,223,184,127,177,165,37,184,78,145,21,28,232,112,39,135,139,132,90,47,179,136,216,253,19,25,96,182,220,64,8,51,113,130,194,13,220,144,194,61,102,135,215,151,171,116,92,148,155,73,205,99,179,151,94,91,202,204,88,143,212,36,34,101,2,57,110,77,147,46,198,49,95,58,235,19,89,202,122,149,124,247,192,171,82,79,34,19,226,18,128,97,38,2,121,70,49,75,34,227,88,147,80,192,149,220,212,79,154,237,214,227,88,139,159,204,27,141,151,74,104,17,214,148,163,222,163,177,210,13,174,205,26,185,89,84,77,140,244,135,52,181,166,183,154,77,93,42,59,254,239,54,201,178,104,76,11,236,76,34,6,140,237,172,21,42,165,93,216,146,178,121,18,64,192,93,243,23,241,150,33,181,147,98,208,186,66,206,115,62,149,181,28,177,93,152,99,245,137,124,249,33,203,89,30,131,212,99,119,101,94,37,181,11,231,105,149,32,109,146,183,243,104,180,140,131,151,188,181,22,183,232,47,146,125,150,214,46,27,160,55,123,129,50,15,206,250,109,236,104,162,123,18,223,67,232,14,158,163,158,4,131,171,209,21,169,8,26,105,187,136,214,234,18,119,14,249,202,65,116,79,106,255,156,43,86,138,226,125,49,94,103,38,85,108,67,191,246,239,252,96,233,107,56,215,193,241,38,9,18,117,62,105,181,39,170,137,48,126,108,242,250,220,139,23,2,120,164,60,137,0,207,22,5,54,138,227,190,111,129,7,114,152,223,201,209,145,231,40,196,148,234,52,245,180,188,68,170,184,90,188,177,178,163,10,45,31,121,202,65,201,211,10,78,41,157,32,179,154,37,203,188,42,166,201,80,190,8,216,215,234,94,110,157,120,22,44,225,140,112,232,146,31,156,193,173,111,100,5,99,154,138,23,129,36,158,110,93,237,221,81,143,113,40,90,188,172,193,124,200,90,186,252,51,237,223,114,72,218,172,229,16,209,154,229,0,218,139,229,95,162,245,138,119,129,120,131,76,101,67,63,144,250,215,172,40,12,223,85,222,96,42,220,66,202,59,103,90,226,86,102,83,240,199,24,91,199,81,41,31,123,37,58,137,147,68,82,183,56,100,78,248,134,124,65,250,135,112,105,94,74,254,88,214,247,165,249,149,69,23,106,26,72,221,58,190,29,41,212,199,119,34,11,146,10,49,105,246,37,245,148,230,192,158,117,139,76,169,172,47,183,63,41,127,180,1,201,146,67,106,27,64,207,228,46,157,193,201,141,150,189,26,98,143,172,12,215,2,252,37,215,3,195,238,60,90,8,106,40,147,149,12,203,43,5,231,116,153,53,156,19,183,191,142,117,191,140,115,105,21,236,132,214,172,65,221,247,186,69,146,109,22,225,197,141,194,37,112,57,98,237,10,214,100,139,53,168,55,95,119,208,204,221,175,61,236,45,22,146,171,252,116,184,230,198,14,120,2,114,185,177,159,42,217,9,134,73,212,72,78,150,65,89,132,197,203,137,210,35,190,230,106,249,5,249,253,72,71,32,117,98,205,71,43,102,55,134,227,198,196,120,193,118,88,41,6,200,179,22,167,212,221,164,149,205,118,217,22,66,123,243,30,66,91,217,132,226,153,203,9,79,183,32,60,45,35,140,11,199,229,164,183,144,123,56,41,35,141,107,252,229,164,189,45,72,123,101,164,73,89,190,156,118,180,5,237,168,128,182,242,62,131,39,120,76,99,98,72,90,17,81,24,242,203,52,253,133,71,75,28,251,217,91,48,85,29,32,96,223,81,205,201,216,137,5,171,220,35,245,50,84,136,72,143,18,56,17,245,221,4,167,228,250,27,105,169,239,111,82,114,162,182,193,182,212,74,147,180,117,108,100,113,192,199,133,233,56,239,13,100,104,55,243,180,75,216,218,64,158,183,12,232,219,42,169,248,159,190,106,112,227,83,55,182,193,86,89,197,147,32,153,165,238,70,122,42,103,79,76,201,237,40,190,79,245,65,112,99,224,13,132,158,101,35,163,241,159,223,79,15,26,183,53,157,184,87,218,144,32,141,22,82,133,105,23,56,50,217,77,99,8,243,96,171,21,107,103,148,122,192,146,137,29,114,145,201,12,218,150,231,77,44,251,238,10,65,76,189,111,234,248,84,116,170,175,178,120,248,164,148,91,46,136,21,215,55,25,133,202,66,193,217,43,95,183,198,86,237,172,86,252,21,138,40,11,165,114,38,49,209,67,26,8,155,27,35,235,19,93,35,49,52,46,219,102,162,232,3,92,185,109,235,122,135,128,150,192,102,49,57,60,130,9,225,191,4,31,11,166,100,97,169,178,86,169,254,248,33,124,110,121,33,240,184,169,84,234,182,161,123,178,142,108,250,86,134,62,229,129,211,95,255,206,70,125,122,192,114,236,92,219,188,180,225,157,105,193,253,69,79,24,104,190,169,246,225,232,86,68,107,69,74,84,200,73,30,200,39,171,217,248,170,48,43,201,50,192,47,87,23,115,63,230,24,248,24,49,130,21,57,90,66,31,34,225,2,126,113,92,78,122,54,179,55,188,9,68,139,249,250,81,3,64,71,179,168,129,171,252,44,194,79,235,151,164,216,79,218,60,153,247,21,233,187,140,93,182,18,211,71,139,132,36,223,19,238,78,193,106,107,24,44,230,132,164,237,60,121,86,219,32,152,53,110,206,91,85,144,179,125,148,156,60,196,5,44,141,100,77,26,15,131,36,152,16,100,236,53,118,174,22,59,114,150,46,15,11,91,223,100,7,236,65,238,81,12,71,64,206,6,188,11,63,21,133,224,158,56,24,34,115,141,252,123,184,140,172,48,223,50,196,196,142,245,236,59,27,190,20,13,114,201,98,164,210,84,182,28,235,96,226,128,5,48,165,200,152,78,169,105,196,155,226,246,148,46,119,59,139,48,169,99,172,28,171,173,44,224,148,34,75,188,138,11,128,115,75,119,139,153,141,55,139,134,53,11,249,203,44,94,243,110,233,39,194,73,195,161,128,197,148,212,50,224,143,11,94,130,28,46,254,56,228,161,150,198,230,233,204,2,176,37,177,53,93,159,193,136,143,34,37,35,179,66,86,155,4,223,42,148,115,206,120,224,247,176,92,56,163,248,37,45,149,16,137,216,72,99,111,3,231,58,55,177,163,6,145,140,36,186,220,85,201,69,8,89,3,103,150,61,77,131,75,102,225,81,174,149,110,53,61,107,249,189,142,166,30,54,230,80,151,14,187,16,149,157,54,217,58,126,122,68,91,209,47,158,253,252,246,77,179,147,54,180,55,173,78,31,184,108,203,64,6,91,225,33,218,153,7,242,24,104,91,22,84,100,133,3,111,103,14,200,243,153,109,57,80,145,21,14,38,107,57,104,80,117,80,138,110,84,163,78,116,96,45,213,158,169,27,205,43,37,172,178,7,52,91,242,202,176,139,185,181,57,183,163,95,48,163,220,250,142,26,160,203,242,109,65,131,0,174,232,146,85,202,209,116,106,86,91,24,60,155,161,154,59,53,109,245,18,162,134,78,214,169,104,115,23,4,209,132,191,214,55,179,210,106,54,165,230,189,124,225,17,105,168,126,162,136,97,22,254,131,149,18,183,80,136,65,40,22,220,168,228,238,231,94,56,19,29,113,57,209,237,48,239,69,2,143,246,4,178,133,187,78,238,106,213,201,166,73,53,138,61,74,160,219,166,9,80,233,46,225,254,39,209,56,71,100,121,10,21,29,156,113,67,226,77,10,213,118,229,143,86,178,178,175,38,202,88,146,202,98,133,12,177,64,81,120,102,82,91,122,4,55,188,24,197,248,73,23,86,202,88,133,75,211,160,148,173,252,121,48,28,106,239,251,90,87,35,96,109,157,88,240,186,172,239,242,119,157,19,13,145,25,111,228,67,107,224,255,224,2,118,49,15,169,20,144,163,77,193,145,125,223,151,45,209,194,157,120,20,5,115,92,203,166,156,18,144,224,244,88,198,158,64,142,198,109,159,57,186,48,66,133,180,130,69,130,31,18,8,100,192,147,189,33,137,225,11,110,6,59,57,36,111,189,40,43,246,76,93,173,252,191,74,169,229,242,108,64,89,30,231,101,82,154,76,179,158,55,58,16,37,91,208,138,150,75,17,21,94,240,171,176,90,132,220,21,39,181,8,81,17,20,197,8,150,40,103,27,220,188,120,242,24,146,172,124,82,252,24,114,155,126,127,150,224,190,178,247,76,210,160,164,116,27,90,236,143,34,156,75,14,183,105,148,63,106,5,37,215,220,220,233,126,20,109,37,99,222,208,168,126,20,97,57,124,236,101,59,200,133,29,229,66,229,85,146,75,86,177,46,211,225,84,57,139,102,21,234,40,215,190,213,234,191,190,168,255,187,169,62,0,0 };
