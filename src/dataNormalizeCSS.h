const char CSS_NORMALIZE[] PROGMEM = R"=====(
html{font-family:sans-serif;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}article,aside,details,figcaption,figure,footer,header,hgroup,main,menu,nav,section,summary{display:block}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}a{background-color:transparent}a:active,a:hover{outline:0}abbr[title]{border-bottom:1px dotted}b,strong{font-weight:bold}dfn{font-style:italic}h1{font-size:2em;margin:.67em 0}mark{background:#ff0;color:#000}small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}sup{top:-.5em}sub{bottom:-.25em}img{border:0}svg:not(:root){overflow:hidden}figure{margin:1em 40px}hr{-moz-box-sizing:content-box;box-sizing:content-box;height:0}pre{overflow:auto}code,kbd,pre,samp{font-family:monospace,monospace;font-size:1em}button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}button{overflow:visible}button,select{text-transform:none}button,html input[type="button"],input[type="reset"],input[type="submit"]{-webkit-appearance:button;cursor:pointer}button[disabled],html input[disabled]{cursor:default}button::-moz-focus-inner,input::-moz-focus-inner{border:0;padding:0}input{line-height:normal}input[type="checkbox"],input[type="radio"]{box-sizing:border-box;padding:0}input[type="number"]::-webkit-inner-spin-button,input[type="number"]::-webkit-outer-spin-button{height:auto}input[type="search"]{-webkit-appearance:textfield;-moz-box-sizing:content-box;-webkit-box-sizing:content-box;box-sizing:content-box}input[type="search"]::-webkit-search-cancel-button,input[type="search"]::-webkit-search-decoration{-webkit-appearance:none}fieldset{border:1px solid silver;margin:0 2px;padding:.35em .625em .75em}legend{border:0;padding:0}textarea{overflow:auto}optgroup{font-weight:bold}table{border-collapse:collapse;border-spacing:0}td,th{padding:0}
)=====";

const uint8_t CSS_NORMALIZE_GZIP[861] PROGMEM = { 31,139,8,0,191,34,95,98,2,255,149,84,237,142,155,58,16,125,149,104,171,74,183,146,137,216,237,199,94,25,221,39,137,242,99,176,7,112,227,47,217,38,155,20,241,238,119,12,132,36,219,108,165,254,2,6,123,230,204,57,103,166,75,70,15,141,179,169,104,192,40,125,230,17,108,44,34,6,213,84,133,137,69,194,83,42,162,250,133,5,200,159,125,76,252,185,44,63,87,197,27,214,7,149,30,255,29,107,39,207,131,129,208,42,203,203,17,66,82,66,35,131,168,36,50,137,9,148,142,172,81,173,0,159,148,179,249,181,15,200,26,231,18,6,214,33,200,252,104,131,235,61,51,160,44,51,104,123,102,225,200,34,138,233,70,236,13,165,63,15,82,69,175,225,204,107,237,196,97,132,94,42,199,4,216,35,68,230,131,107,3,198,200,142,84,213,173,39,149,213,202,98,49,93,168,142,152,161,129,46,64,171,214,242,26,34,230,191,115,34,110,93,250,103,39,136,153,224,116,220,127,89,83,88,103,177,234,80,181,93,162,238,118,157,146,18,237,158,37,52,244,59,225,221,185,17,134,26,196,33,247,98,101,33,156,118,129,167,64,12,123,8,104,211,8,28,168,163,35,145,195,59,71,112,6,215,167,12,33,211,86,215,97,151,84,210,184,31,106,23,136,147,162,118,41,57,195,159,253,105,35,233,21,229,88,179,72,240,108,59,43,248,54,131,170,157,150,163,108,236,28,140,233,172,145,171,68,61,138,177,123,94,130,36,25,127,65,83,45,42,109,127,188,162,217,148,35,125,30,110,16,243,79,77,83,86,51,236,79,101,89,142,209,128,214,55,41,254,37,181,99,79,40,122,127,19,125,253,254,185,154,104,190,176,84,121,23,85,86,142,7,36,142,168,225,15,185,207,153,146,243,188,216,126,71,147,115,15,75,215,197,246,37,71,148,105,23,58,136,163,120,108,39,153,120,32,239,124,25,50,131,141,118,111,124,214,100,156,141,117,113,226,51,117,248,173,244,167,177,11,67,97,220,47,162,243,148,241,42,219,242,44,51,233,145,67,213,7,225,85,113,79,41,215,74,208,39,55,10,71,198,62,212,146,76,135,44,130,241,119,3,101,156,117,164,183,64,182,190,85,87,174,8,213,88,247,212,161,101,202,250,62,49,231,211,108,125,34,132,236,206,242,136,145,89,96,152,101,80,182,163,217,76,83,134,245,99,157,181,57,211,21,222,81,69,85,107,188,84,152,83,14,211,212,78,54,108,92,48,179,81,151,19,29,173,131,205,4,100,151,206,30,255,123,154,227,79,123,118,27,164,193,194,244,46,70,82,25,69,193,225,178,27,192,123,4,42,34,144,207,73,42,209,135,72,45,120,167,136,214,176,148,220,209,188,0,97,148,251,219,226,107,112,88,46,73,108,160,215,105,185,196,249,164,96,227,68,31,11,101,45,45,140,233,222,239,241,213,44,149,7,41,179,168,229,56,29,29,110,29,106,137,7,208,227,109,63,162,67,113,32,225,223,183,14,180,27,158,242,72,174,46,89,167,243,244,190,198,114,199,246,166,198,240,180,39,116,11,55,19,180,34,122,101,139,91,241,63,60,79,107,225,254,252,176,0,159,252,119,39,3,113,46,186,199,50,100,221,27,133,90,86,127,242,255,229,226,95,141,199,67,12,87,252,115,164,16,25,134,126,212,242,135,87,36,10,23,32,239,142,71,29,77,214,157,90,34,67,94,164,206,251,49,58,173,228,38,42,77,147,176,142,199,230,197,95,37,218,126,165,117,178,217,254,120,153,30,175,121,183,104,108,209,202,71,142,89,135,240,126,240,47,179,250,251,250,77,217,189,151,189,77,147,171,193,71,228,151,151,106,249,145,151,193,82,64,178,212,13,215,130,255,3,4,241,118,208,151,7,0,0 };
