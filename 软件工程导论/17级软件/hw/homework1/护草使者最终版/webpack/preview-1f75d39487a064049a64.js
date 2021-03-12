(window.webpackJsonp=window.webpackJsonp||[]).push([[16],{"+Cau":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.receiverMap=t.createMessageBucket=void 0
var r=a(n("MVZn")),l=a(n("zkrS")),s=n("upRB")
t.createMessageBucket=function(i){var o=function(e){var t=1<arguments.length&&void 0!==arguments[1]?arguments[1]:{},n=2<arguments.length&&void 0!==arguments[2]?arguments[2]:"*"
return e&&window.parent.postMessage(JSON.stringify({event:e,payload:t}),n)},e=function(t){if(t.source!==window&&!t.origin.includes("qiyukf")&&t.data&&"string"==typeof t.data)try{var e=JSON.parse(t.data),n=e.event,a=e.payload,r=void 0===a?{}:a
i[n]&&i[n](o,{type:n,payload:r,event:t})}catch(e){console.warn("[receive] error message data",e,t)}}
return window.addEventListener("message",e),{send:o,clear:function(){return window.removeEventListener("message",e)}}}
var i={"message:get:preview-state":function(e){var t=u(),n=t.state,a=t.isHighlight
e("message:data:preview-state",(0,r.default)({},n.model.current,{isHighlight:a}))},"message:set:preview-state":function(e,t){var n=t.payload,a=n.isHighlight,r=n.screenCid,i=u(),o=i.state.model,l=o.current,s=o.screens,c=i.dispatch
if(void 0!==a&&c({type:"reducer:preview-toolbar:update:highlight",payload:{isHighlight:a}}),l.screenCid&&void 0!==r&&r!==l.screenCid){if(!s.find(function(e){return e.cid===r}))return console.warn("[message:set:preview-state] invalid screenCid")
c({type:"entry:sync-runner:set-screen",payload:{cid:r}})}},"message:get:screen-list":function(e){var t=l.default.MB.webpackInterface.store.getState().model,n=t.current
e("message:data:screen-list",t.screens.filter(function(e){return e.project_cid===n.projectCid}).map(function(e){return{cid:e.cid,name:e.name,position:e.position,parent_cid:e.parent_cid,project_cid:e.project_cid}}))},"message:get:notification-state":function(e){var t=(l.default.MB.notification&&l.default.MB.notification.store&&l.default.MB.notification.store.getState()||{}).notifications
e("message:data:notification-state",{unreadCount:t?t.notifications.unreadNum:0})},"message:get:notification-list":function(e){var t=(l.default.MB.notification&&l.default.MB.notification.store&&l.default.MB.notification.store.getState()||{}).notifications
e("message:data:notification-list",t?t.notifications.notifications:[])}}
t.receiverMap=i
var u=function(){var e=l.default.MB.webpackInterface.store,t=e.getState,n=e.dispatch,a=t(),r=(0,s.getIsHighlight)(a),i=a.model.current.projectCid,o=i&&a.model.projects.find(function(e){return e.cid===i})
return{getState:t,dispatch:n,state:a,project:o,isHighlight:r}}},"+IKJ":function(e,t,n){"use strict"
function m(){return(m=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t]
for(var a in n)Object.prototype.hasOwnProperty.call(n,a)&&(e[a]=n[a])}return e}).apply(this,arguments)}function i(e){return e.charAt(0).toUpperCase()+e.slice(1)}n.r(t),n.d(t,"adjustHue",function(){return ge}),n.d(t,"animation",function(){return Je}),n.d(t,"backgroundImages",function(){return Ze}),n.d(t,"backgrounds",function(){return Ke}),n.d(t,"between",function(){return v}),n.d(t,"border",function(){return Qe}),n.d(t,"borderColor",function(){return j}),n.d(t,"borderRadius",function(){return $e}),n.d(t,
"borderStyle",function(){return et}),n.d(t,"borderWidth",function(){return tt}),n.d(t,"buttons",function(){return ot}),n.d(t,"clearFix",function(){return y}),n.d(t,"complement",function(){return ye}),n.d(t,"cover",function(){return b}),n.d(t,"darken",function(){return we}),n.d(t,"desaturate",function(){return ke}),n.d(t,"directionalProperty",function(){return r}),n.d(t,"ellipsis",function(){return S}),n.d(t,"em",function(){return s}),n.d(t,"fluidRange",function(){return w}),n.d(t,"fontFace",function(){
return E}),n.d(t,"getLuminance",function(){return Ce}),n.d(t,"getValueAndUnit",function(){return g}),n.d(t,"grayscale",function(){return xe}),n.d(t,"invert",function(){return Te}),n.d(t,"hideText",function(){return k}),n.d(t,"hideVisually",function(){return C}),n.d(t,"hiDPI",function(){return x}),n.d(t,"hsl",function(){return ie}),n.d(t,"hsla",function(){return oe}),n.d(t,"lighten",function(){return Me}),n.d(t,"margin",function(){return lt}),n.d(t,"mix",function(){return Ie}),n.d(t,"modularScale",function(
){return p}),n.d(t,"normalize",function(){return T}),n.d(t,"opacify",function(){return Re}),n.d(t,"padding",function(){return st}),n.d(t,"parseToHsl",function(){return $}),n.d(t,"parseToRgb",function(){return Q}),n.d(t,"placeholder",function(){return _}),n.d(t,"position",function(){return ut}),n.d(t,"radialGradient",function(){return P}),n.d(t,"readableColor",function(){return Le}),n.d(t,"rem",function(){return h}),n.d(t,"retinaImage",function(){return I}),n.d(t,"rgb",function(){return le}),n.d(t,"rgba",
function(){return se}),n.d(t,"saturate",function(){return Ae}),n.d(t,"selection",function(){return N}),n.d(t,"setHue",function(){return De}),n.d(t,"setLightness",function(){return Fe}),n.d(t,"setSaturation",function(){return We}),n.d(t,"shade",function(){return ze}),n.d(t,"size",function(){return dt}),n.d(t,"stripUnit",function(){return l}),n.d(t,"textInputs",function(){return ht}),n.d(t,"timingFunctions",function(){return L}),n.d(t,"tint",function(){return He}),n.d(t,"toColorString",function(){return he}),
n.d(t,"transitions",function(){return mt}),n.d(t,"transparentize",function(){return Xe}),n.d(t,"triangle",function(){return O}),n.d(t,"wordWrap",function(){return F})
var u=["Top","Right","Bottom","Left"]
function d(e,t){if(!e)return t.toLowerCase()
var n=e.split("-")
if(1<n.length)return n.splice(1,0,t),n.reduce(function(e,t){return""+e+i(t)})
var a=e.replace(/([a-z])([A-Z])/g,"$1"+t+"$2")
return e===a?""+e+t:a}function r(e){for(var t=arguments.length,n=new Array(1<t?t-1:0),a=1;a<t;a++)n[a-1]=arguments[a]
var r=n[0],i=n[1],o=void 0===i?r:i,l=n[2],s=void 0===l?r:l,c=n[3]
return function(e,t){for(var n={},a=0;a<t.length;a+=1)(t[a]||0===t[a])&&(n[d(e,u[a])]=t[a])
return n}(e,[r,o,s,void 0===c?o:c])}function o(e,t){return e.substr(-t.length)===t}function l(e){var t=parseFloat(e)
return isNaN(t)?e:t}var a=function(r){return function(e,t){void 0===t&&(t="16px")
var n=e,a=t
if("string"==typeof e){if(!o(e,"px"))throw new Error('Expected a string ending in "px" or a number passed as the first argument to '+r+'(), got "'+e+'" instead.')
n=l(e)}if("string"==typeof t){if(!o(t,"px"))throw new Error('Expected a string ending in "px" or a number passed as the second argument to '+r+'(), got "'+t+'" instead.')
a=l(t)}if("string"==typeof n)throw new Error('Passed invalid pixel value ("'+e+'") to '+r+'(), please pass a value like "12px" or 12.')
if("string"==typeof a)throw new Error('Passed invalid base value ("'+t+'") to '+r+'(), please pass a value like "12px" or 12.')
return""+n/a+r}},s=a("em"),c=/^([+-]?(?:\d+|\d*\.\d+))([a-z]*|%)$/
function g(e){if("string"!=typeof e)return[e,""]
var t=e.match(c)
return t?[parseFloat(e),t[2]]:[e,void 0]}var f={minorSecond:1.067,majorSecond:1.125,minorThird:1.2,majorThird:1.25,perfectFourth:1.333,augFourth:1.414,perfectFifth:1.5,minorSixth:1.6,goldenSection:1.618,majorSixth:1.667,minorSeventh:1.778,majorSeventh:1.875,octave:2,majorTenth:2.5,majorEleventh:2.667,majorTwelfth:3,doubleOctave:4}
function p(e,t,n){if(void 0===t&&(t="1em"),void 0===n&&(n="perfectFourth"),"number"!=typeof e)throw new Error("Please provide a number of steps to the modularScale helper.")
if("string"==typeof n&&!f[n])throw new Error("Please pass a number or one of the predefined scales to the modularScale helper as the ratio.")
var a="string"==typeof t?l(t):t,r="string"==typeof n?function(e){return f[e]}(n):n
if("string"==typeof a)throw new Error('Invalid value passed as base to modularScale, expected number or em string but got "'+t+'"')
return a*Math.pow(r,e)+"em"}var h=a("rem")
function v(e,t,n,a){void 0===n&&(n="320px"),void 0===a&&(a="1200px")
var r=g(e),i=r[0],o=r[1],l=g(t),s=l[0],c=l[1],u=g(n),d=u[0],f=u[1],p=g(a),h=p[0],m=p[1]
if("number"!=typeof d||"number"!=typeof h||!f||!m||f!==m)throw new Error("minScreen and maxScreen must be provided as stringified numbers with the same units.")
if("number"!=typeof i||"number"!=typeof s||!o||!c||o!==c)throw new Error("fromSize and toSize must be provided as stringified numbers with the same units.")
var v=(i-s)/(d-h)
return"calc("+(s-v*h).toFixed(2)+o+" + "+(100*v).toFixed(2)+"vw)"}function y(e){var t
return void 0===e&&(e="&"),(t={})[e+"::after"]={clear:"both",content:'""',display:"table"},t}function b(e){return void 0===e&&(e=0),{position:"absolute",top:e,right:e,bottom:e,left:e}}function S(e){return void 0===e&&(e="100%"),{display:"inline-block",maxWidth:e,overflow:"hidden",textOverflow:"ellipsis",whiteSpace:"nowrap",wordWrap:"normal"}}function w(e,t,n){if(void 0===t&&(t="320px"),void 0===n&&(n="1200px"),!Array.isArray(e)&&"object"!=typeof e||null===e)throw new Error(
"expects either an array of objects or a single object with the properties prop, fromSize, and toSize.")
if(Array.isArray(e)){var a={},r={},i=e,o=Array.isArray(i),l=0
for(i=o?i:i[Symbol.iterator]();;){var s,c,u
if(o){if(l>=i.length)break
u=i[l++]}else{if((l=i.next()).done)break
u=l.value}var d=u
if(!d.prop||!d.fromSize||!d.toSize)throw new Error("expects the objects in the first argument array to have the properties `prop`, `fromSize`, and `toSize`.")
r[d.prop]=d.fromSize,a["@media (min-width: "+t+")"]=m({},a["@media (min-width: "+t+")"],((s={})[d.prop]=v(d.fromSize,d.toSize,t,n),s)),a["@media (min-width: "+n+")"]=m({},a["@media (min-width: "+n+")"],((c={})[d.prop]=d.toSize,c))}return m({},r,a)}var f,p,h
if(!e.prop||!e.fromSize||!e.toSize)throw new Error("expects the first argument object to have the properties `prop`, `fromSize`, and `toSize`.")
return(h={})[e.prop]=e.fromSize,h["@media (min-width: "+t+")"]=((f={})[e.prop]=v(e.fromSize,e.toSize,t,n),f),h["@media (min-width: "+n+")"]=((p={})[e.prop]=e.toSize,p),h}function E(e){var t=e.fontFamily,n=e.fontFilePath,a=e.fontStretch,r=e.fontStyle,i=e.fontVariant,o=e.fontWeight,l=e.fileFormats,s=void 0===l?["eot","woff2","woff","ttf","svg"]:l,c=e.localFonts,u=e.unicodeRange,d=e.fontDisplay,f=e.fontVariationSettings,p=e.fontFeatureSettings
if(!t)throw new Error("fontFace expects a name of a font-family.")
if(!n&&!c)throw new Error("fontFace expects either the path to the font file(s) or a name of a local copy.")
if(c&&!Array.isArray(c))throw new Error("fontFace expects localFonts to be an array.")
if(!Array.isArray(s))throw new Error("fontFace expects fileFormats to be an array.")
var h={"@font-face":{fontFamily:t,src:function(e,t,n){var a=[]
return t&&a.push(function(e){return e.map(function(e){return'local("'+e+'")'}).join(", ")}(t)),e&&a.push(function(t,e){return e.map(function(e){return'url("'+t+"."+e+'")'}).join(", ")}(e,n)),a.join(", ")}(n,c,s),unicodeRange:u,fontStretch:a,fontStyle:r,fontVariant:i,fontWeight:o,fontDisplay:d,fontVariationSettings:f,fontFeatureSettings:p}}
return JSON.parse(JSON.stringify(h))}function k(){return{textIndent:"101%",overflow:"hidden",whiteSpace:"nowrap"}}function C(){return{border:"0",clip:"rect(0 0 0 0)",clipPath:"inset(50%)",height:"1px",margin:"-1px",overflow:"hidden",padding:"0",position:"absolute",whiteSpace:"nowrap",width:"1px"}}function x(e){return void 0===e&&(e=1.3),
"\n    @media only screen and (-webkit-min-device-pixel-ratio: "+e+"),\n    only screen and (min--moz-device-pixel-ratio: "+e+"),\n    only screen and (-o-min-device-pixel-ratio: "+e+"/1),\n    only screen and (min-resolution: "+Math.round(96*e)+"dpi),\n    only screen and (min-resolution: "+e+"dppx)\n  "}function T(){var e
return[(e={html:{lineHeight:"1.15",textSizeAdjust:"100%"},body:{margin:"0"},h1:{fontSize:"2em",margin:"0.67em 0"},hr:{boxSizing:"content-box",height:"0",overflow:"visible"},pre:{fontFamily:"monospace, monospace",fontSize:"1em"},a:{backgroundColor:"transparent"},"abbr[title]":{borderBottom:"none",textDecoration:"underline"}},e["b,\n    strong"]={fontWeight:"bolder"},e["code,\n    kbd,\n    samp"]={fontFamily:"monospace, monospace",fontSize:"1em"},e.small={fontSize:"80%"},e["sub,\n    sup"]={fontSize:"75%",
lineHeight:"0",position:"relative",verticalAlign:"baseline"},e.sub={bottom:"-0.25em"},e.sup={top:"-0.5em"},e.img={borderStyle:"none"},e["button,\n    input,\n    optgroup,\n    select,\n    textarea"]={fontFamily:"inherit",fontSize:"100%",lineHeight:"1.15",margin:"0"},e["button,\n    input"]={overflow:"visible"},e["button,\n    select"]={textTransform:"none"},e['button,\n    html [type="button"],\n    [type="reset"],\n    [type="submit"]']={WebkitAppearance:"button"},
e['button::-moz-focus-inner,\n    [type="button"]::-moz-focus-inner,\n    [type="reset"]::-moz-focus-inner,\n    [type="submit"]::-moz-focus-inner']={borderStyle:"none",padding:"0"},e['button:-moz-focusring,\n    [type="button"]:-moz-focusring,\n    [type="reset"]:-moz-focusring,\n    [type="submit"]:-moz-focusring']={outline:"1px dotted ButtonText"},e.fieldset={padding:"0.35em 0.625em 0.75em"},e.legend={boxSizing:"border-box",color:"inherit",display:"table",maxWidth:"100%",padding:"0",whiteSpace:"normal"},
e.progress={verticalAlign:"baseline"},e.textarea={overflow:"auto"},e['[type="checkbox"],\n    [type="radio"]']={boxSizing:"border-box",padding:"0"},e['[type="number"]::-webkit-inner-spin-button,\n    [type="number"]::-webkit-outer-spin-button']={height:"auto"},e['[type="search"]']={WebkitAppearance:"textfield",outlineOffset:"-2px"},e['[type="search"]::-webkit-search-decoration']={WebkitAppearance:"none"},e["::-webkit-file-upload-button"]={WebkitAppearance:"button",font:"inherit"},e.details={display:"block"}
,e.summary={display:"list-item"},e.template={display:"none"},e["[hidden]"]={display:"none"},e),{"abbr[title]":{textDecoration:"underline dotted"}}]}function _(e,t){var n
return void 0===t&&(t="&"),(n={})[t+"::-webkit-input-placeholder"]=m({},e),n[t+":-moz-placeholder"]=m({},e),n[t+"::-moz-placeholder"]=m({},e),n[t+":-ms-input-placeholder"]=m({},e),n}function M(){var e=function(e,t){return t||(t=e.slice(0)),e.raw=t,e}(["radial-gradient(","","","",")"])
return M=function(){return e},e}function P(e){var t=e.colorStops,n=e.extent,a=e.fallback,r=e.position,i=e.shape
if(!t||t.length<2)throw new Error("radialGradient requries at least 2 color-stops to properly render.")
return{backgroundColor:a||function(e){return e[0].split(" ")[0]}(t),backgroundImage:function(e){for(var t="",n=0;n<e.length;n+=1)t+=e[n],3===n&&(n+1<1||arguments.length<=n+1?void 0:arguments[n+1])&&((arguments.length<=1?void 0:arguments[1])||(arguments.length<=2?void 0:arguments[2])||(arguments.length<=3?void 0:arguments[3]))?(t=t.slice(0,-1),t+=", "+(n+1<1||arguments.length<=n+1?void 0:arguments[n+1])):3!==n||n+1<1||arguments.length<=n+1||!arguments[n+1]||(arguments.length<=1?void 0:arguments[1])||(
arguments.length<=2?void 0:arguments[2])||(arguments.length<=3?void 0:arguments[3])?(n+1<1||arguments.length<=n+1?void 0:arguments[n+1])&&(t+=(n+1<1||arguments.length<=n+1?void 0:arguments[n+1])+" "):t+=""+(n+1<1||arguments.length<=n+1?void 0:arguments[n+1])
return t.trim()}(M(),r,i,n,t.join(", "))}}function I(e,t,n,a,r){var i
if(void 0===n&&(n="png"),void 0===r&&(r="_2x"),!e)throw new Error("Please supply a filename to retinaImage() as the first argument.")
var o=n.replace(/^\./,""),l=a?a+"."+o:""+e+r+"."+o
return(i={backgroundImage:"url("+e+"."+o+")"})[x()]=m({backgroundImage:"url("+l+")"},t?{backgroundSize:t}:{}),i}function N(e,t){var n
return void 0===t&&(t=""),(n={})[t+"::-moz-selection"]=m({},e),n[t+"::selection"]=m({},e),n}var R={easeInBack:"cubic-bezier(0.600, -0.280, 0.735, 0.045)",easeInCirc:"cubic-bezier(0.600,  0.040, 0.980, 0.335)",easeInCubic:"cubic-bezier(0.550,  0.055, 0.675, 0.190)",easeInExpo:"cubic-bezier(0.950,  0.050, 0.795, 0.035)",easeInQuad:"cubic-bezier(0.550,  0.085, 0.680, 0.530)",easeInQuart:"cubic-bezier(0.895,  0.030, 0.685, 0.220)",easeInQuint:"cubic-bezier(0.755,  0.050, 0.855, 0.060)",
easeInSine:"cubic-bezier(0.470,  0.000, 0.745, 0.715)",easeOutBack:"cubic-bezier(0.175,  0.885, 0.320, 1.275)",easeOutCubic:"cubic-bezier(0.215,  0.610, 0.355, 1.000)",easeOutCirc:"cubic-bezier(0.075,  0.820, 0.165, 1.000)",easeOutExpo:"cubic-bezier(0.190,  1.000, 0.220, 1.000)",easeOutQuad:"cubic-bezier(0.250,  0.460, 0.450, 0.940)",easeOutQuart:"cubic-bezier(0.165,  0.840, 0.440, 1.000)",easeOutQuint:"cubic-bezier(0.230,  1.000, 0.320, 1.000)",easeOutSine:"cubic-bezier(0.390,  0.575, 0.565, 1.000)",
easeInOutBack:"cubic-bezier(0.680, -0.550, 0.265, 1.550)",easeInOutCirc:"cubic-bezier(0.785,  0.135, 0.150, 0.860)",easeInOutCubic:"cubic-bezier(0.645,  0.045, 0.355, 1.000)",easeInOutExpo:"cubic-bezier(1.000,  0.000, 0.000, 1.000)",easeInOutQuad:"cubic-bezier(0.455,  0.030, 0.515, 0.955)",easeInOutQuart:"cubic-bezier(0.770,  0.000, 0.175, 1.000)",easeInOutQuint:"cubic-bezier(0.860,  0.000, 0.070, 1.000)",easeInOutSine:"cubic-bezier(0.445,  0.050, 0.550, 0.950)"}
function L(e){return function(e){return R[e]}(e)}function j(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return r.apply(void 0,["borderColor"].concat(t))}var A=function(e,t,n){switch(e){case"top":return"0 "+n[0]/2+n[1]+" "+t[0]+t[1]+" "+n[0]/2+n[1]
case"left":return""+t[0]/2+t[1]+" "+n[0]+n[1]+" "+t[0]/2+t[1]+" 0"
case"bottom":return""+t[0]+t[1]+" "+n[0]/2+n[1]+" 0 "+n[0]/2+n[1]
case"right":return""+t[0]/2+t[1]+" 0 "+t[0]/2+t[1]+" "+n[0]+n[1]
default:throw new Error("Passed invalid argument to triangle, please pass correct pointingDirection e.g. 'right'.")}},B=["bottom","left","top","right"],D=/(\d*\.?\d*)/
function O(e){var t=e.pointingDirection,n=e.height,a=e.width,r=e.foregroundColor,i=e.backgroundColor,o=void 0===i?"transparent":i,l=[parseFloat(a),String(a).replace(D,"")||"px"],s=[parseFloat(n),String(n).replace(D,"")||"px"]
if(isNaN(s[0])||isNaN(l[0]))throw new Error("Passed an invalid value to `height` or `width`. Please provide a pixel based unit")
var c=B.indexOf(t)
return m({width:"0",height:"0",borderWidth:A(t,s,l),borderStyle:"solid"},j.apply(void 0,Array.from({length:4}).map(function(e,t){return t===c?r:o})))}function F(e){return void 0===e&&(e="break-word"),{overflowWrap:e,wordWrap:e,wordBreak:"break-word"===e?"break-all":e}}function q(e){return Math.round(255*e)}function W(e,t,n){return q(e)+","+q(t)+","+q(n)}function U(e,t,n,a){if(void 0===a&&(a=W),0===t)return a(n,n,n)
var r=e%360/60,i=(1-Math.abs(2*n-1))*t,o=i*(1-Math.abs(r%2-1)),l=0,s=0,c=0
0<=r&&r<1?(l=i,s=o):1<=r&&r<2?(l=o,s=i):2<=r&&r<3?(s=i,c=o):3<=r&&r<4?(s=o,c=i):4<=r&&r<5?(l=o,c=i):5<=r&&r<6&&(l=i,c=o)
var u=n-i/2
return a(l+u,s+u,c+u)}var z={aliceblue:"f0f8ff",antiquewhite:"faebd7",aqua:"00ffff",aquamarine:"7fffd4",azure:"f0ffff",beige:"f5f5dc",bisque:"ffe4c4",black:"000",blanchedalmond:"ffebcd",blue:"0000ff",blueviolet:"8a2be2",brown:"a52a2a",burlywood:"deb887",cadetblue:"5f9ea0",chartreuse:"7fff00",chocolate:"d2691e",coral:"ff7f50",cornflowerblue:"6495ed",cornsilk:"fff8dc",crimson:"dc143c",cyan:"00ffff",darkblue:"00008b",darkcyan:"008b8b",darkgoldenrod:"b8860b",darkgray:"a9a9a9",darkgreen:"006400",
darkgrey:"a9a9a9",darkkhaki:"bdb76b",darkmagenta:"8b008b",darkolivegreen:"556b2f",darkorange:"ff8c00",darkorchid:"9932cc",darkred:"8b0000",darksalmon:"e9967a",darkseagreen:"8fbc8f",darkslateblue:"483d8b",darkslategray:"2f4f4f",darkslategrey:"2f4f4f",darkturquoise:"00ced1",darkviolet:"9400d3",deeppink:"ff1493",deepskyblue:"00bfff",dimgray:"696969",dimgrey:"696969",dodgerblue:"1e90ff",firebrick:"b22222",floralwhite:"fffaf0",forestgreen:"228b22",fuchsia:"ff00ff",gainsboro:"dcdcdc",ghostwhite:"f8f8ff",
gold:"ffd700",goldenrod:"daa520",gray:"808080",green:"008000",greenyellow:"adff2f",grey:"808080",honeydew:"f0fff0",hotpink:"ff69b4",indianred:"cd5c5c",indigo:"4b0082",ivory:"fffff0",khaki:"f0e68c",lavender:"e6e6fa",lavenderblush:"fff0f5",lawngreen:"7cfc00",lemonchiffon:"fffacd",lightblue:"add8e6",lightcoral:"f08080",lightcyan:"e0ffff",lightgoldenrodyellow:"fafad2",lightgray:"d3d3d3",lightgreen:"90ee90",lightgrey:"d3d3d3",lightpink:"ffb6c1",lightsalmon:"ffa07a",lightseagreen:"20b2aa",lightskyblue:"87cefa",
lightslategray:"789",lightslategrey:"789",lightsteelblue:"b0c4de",lightyellow:"ffffe0",lime:"0f0",limegreen:"32cd32",linen:"faf0e6",magenta:"f0f",maroon:"800000",mediumaquamarine:"66cdaa",mediumblue:"0000cd",mediumorchid:"ba55d3",mediumpurple:"9370db",mediumseagreen:"3cb371",mediumslateblue:"7b68ee",mediumspringgreen:"00fa9a",mediumturquoise:"48d1cc",mediumvioletred:"c71585",midnightblue:"191970",mintcream:"f5fffa",mistyrose:"ffe4e1",moccasin:"ffe4b5",navajowhite:"ffdead",navy:"000080",oldlace:"fdf5e6",
olive:"808000",olivedrab:"6b8e23",orange:"ffa500",orangered:"ff4500",orchid:"da70d6",palegoldenrod:"eee8aa",palegreen:"98fb98",paleturquoise:"afeeee",palevioletred:"db7093",papayawhip:"ffefd5",peachpuff:"ffdab9",peru:"cd853f",pink:"ffc0cb",plum:"dda0dd",powderblue:"b0e0e6",purple:"800080",rebeccapurple:"639",red:"f00",rosybrown:"bc8f8f",royalblue:"4169e1",saddlebrown:"8b4513",salmon:"fa8072",sandybrown:"f4a460",seagreen:"2e8b57",seashell:"fff5ee",sienna:"a0522d",silver:"c0c0c0",skyblue:"87ceeb",
slateblue:"6a5acd",slategray:"708090",slategrey:"708090",snow:"fffafa",springgreen:"00ff7f",steelblue:"4682b4",tan:"d2b48c",teal:"008080",thistle:"d8bfd8",tomato:"ff6347",turquoise:"40e0d0",violet:"ee82ee",wheat:"f5deb3",white:"fff",whitesmoke:"f5f5f5",yellow:"ff0",yellowgreen:"9acd32"}
var Y=/^#[a-fA-F0-9]{6}$/,H=/^#[a-fA-F0-9]{8}$/,V=/^#[a-fA-F0-9]{3}$/,X=/^#[a-fA-F0-9]{4}$/,J=/^rgb\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*,\s*(\d{1,3})\s*\)$/,Z=/^rgba\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*,\s*(\d{1,3})\s*,\s*([-+]?[0-9]*[.]?[0-9]+)\s*\)$/,K=/^hsl\(\s*(\d{0,3}[.]?[0-9]+)\s*,\s*(\d{1,3})%\s*,\s*(\d{1,3})%\s*\)$/,G=/^hsla\(\s*(\d{0,3}[.]?[0-9]+)\s*,\s*(\d{1,3})%\s*,\s*(\d{1,3})%\s*,\s*([-+]?[0-9]*[.]?[0-9]+)\s*\)$/
function Q(e){if("string"!=typeof e)throw new Error("Passed an incorrect argument to a color function, please pass a string representation of a color.")
var t=function(e){if("string"!=typeof e)return e
var t=e.toLowerCase()
return z[t]?"#"+z[t]:e}(e)
if(t.match(Y))return{red:parseInt(""+t[1]+t[2],16),green:parseInt(""+t[3]+t[4],16),blue:parseInt(""+t[5]+t[6],16)}
if(t.match(H)){var n=parseFloat((parseInt(""+t[7]+t[8],16)/255).toFixed(2))
return{red:parseInt(""+t[1]+t[2],16),green:parseInt(""+t[3]+t[4],16),blue:parseInt(""+t[5]+t[6],16),alpha:n}}if(t.match(V))return{red:parseInt(""+t[1]+t[1],16),green:parseInt(""+t[2]+t[2],16),blue:parseInt(""+t[3]+t[3],16)}
if(t.match(X)){var a=parseFloat((parseInt(""+t[4]+t[4],16)/255).toFixed(2))
return{red:parseInt(""+t[1]+t[1],16),green:parseInt(""+t[2]+t[2],16),blue:parseInt(""+t[3]+t[3],16),alpha:a}}var r=J.exec(t)
if(r)return{red:parseInt(""+r[1],10),green:parseInt(""+r[2],10),blue:parseInt(""+r[3],10)}
var i=Z.exec(t)
if(i)return{red:parseInt(""+i[1],10),green:parseInt(""+i[2],10),blue:parseInt(""+i[3],10),alpha:parseFloat(""+i[4])}
var o=K.exec(t)
if(o){var l="rgb("+U(parseInt(""+o[1],10),parseInt(""+o[2],10)/100,parseInt(""+o[3],10)/100)+")",s=J.exec(l)
if(!s)throw new Error("Couldn't generate valid rgb string from "+t+", it returned "+l+".")
return{red:parseInt(""+s[1],10),green:parseInt(""+s[2],10),blue:parseInt(""+s[3],10)}}var c=G.exec(t)
if(c){var u="rgb("+U(parseInt(""+c[1],10),parseInt(""+c[2],10)/100,parseInt(""+c[3],10)/100)+")",d=J.exec(u)
if(!d)throw new Error("Couldn't generate valid rgb string from "+t+", it returned "+u+".")
return{red:parseInt(""+d[1],10),green:parseInt(""+d[2],10),blue:parseInt(""+d[3],10),alpha:parseFloat(""+c[4])}}throw new Error("Couldn't parse the color string. Please provide the color as a string in hex, rgb, rgba, hsl or hsla notation.")}function $(e){return function(e){var t,n=e.red/255,a=e.green/255,r=e.blue/255,i=Math.max(n,a,r),o=Math.min(n,a,r),l=(i+o)/2
if(i===o)return void 0!==e.alpha?{hue:0,saturation:0,lightness:l,alpha:e.alpha}:{hue:0,saturation:0,lightness:l}
var s=i-o,c=.5<l?s/(2-i-o):s/(i+o)
switch(i){case n:t=(a-r)/s+(a<r?6:0)
break
case a:t=(r-n)/s+2
break
default:t=(n-a)/s+4}return t*=60,void 0!==e.alpha?{hue:t,saturation:c,lightness:l,alpha:e.alpha}:{hue:t,saturation:c,lightness:l}}(Q(e))}var ee=function(e){return 7===e.length&&e[1]===e[2]&&e[3]===e[4]&&e[5]===e[6]?"#"+e[1]+e[3]+e[5]:e}
function te(e){var t=e.toString(16)
return 1===t.length?"0"+t:t}function ne(e){return te(Math.round(255*e))}function ae(e,t,n){return ee("#"+ne(e)+ne(t)+ne(n))}function re(e,t,n){return U(e,t,n,ae)}function ie(e,t,n){if("number"==typeof e&&"number"==typeof t&&"number"==typeof n)return re(e,t,n)
if("object"==typeof e&&void 0===t&&void 0===n)return re(e.hue,e.saturation,e.lightness)
throw new Error("Passed invalid arguments to hsl, please pass multiple numbers e.g. hsl(360, 0.75, 0.4) or an object e.g. rgb({ hue: 255, saturation: 0.4, lightness: 0.75 }).")}function oe(e,t,n,a){if("number"==typeof e&&"number"==typeof t&&"number"==typeof n&&"number"==typeof a)return 1<=a?re(e,t,n):"rgba("+U(e,t,n)+","+a+")"
if("object"==typeof e&&void 0===t&&void 0===n&&void 0===a)return 1<=e.alpha?re(e.hue,e.saturation,e.lightness):"rgba("+U(e.hue,e.saturation,e.lightness)+","+e.alpha+")"
throw new Error("Passed invalid arguments to hsla, please pass multiple numbers e.g. hsl(360, 0.75, 0.4, 0.7) or an object e.g. rgb({ hue: 255, saturation: 0.4, lightness: 0.75, alpha: 0.7 }).")}function le(e,t,n){if("number"==typeof e&&"number"==typeof t&&"number"==typeof n)return ee("#"+te(e)+te(t)+te(n))
if("object"==typeof e&&void 0===t&&void 0===n)return ee("#"+te(e.red)+te(e.green)+te(e.blue))
throw new Error("Passed invalid arguments to rgb, please pass multiple numbers e.g. rgb(255, 205, 100) or an object e.g. rgb({ red: 255, green: 205, blue: 100 }).")}function se(e,t,n,a){if("string"==typeof e&&"number"==typeof t){var r=Q(e)
return"rgba("+r.red+","+r.green+","+r.blue+","+t+")"}if("number"==typeof e&&"number"==typeof t&&"number"==typeof n&&"number"==typeof a)return 1<=a?le(e,t,n):"rgba("+e+","+t+","+n+","+a+")"
if("object"==typeof e&&void 0===t&&void 0===n&&void 0===a)return 1<=e.alpha?le(e.red,e.green,e.blue):"rgba("+e.red+","+e.green+","+e.blue+","+e.alpha+")"
throw new Error("Passed invalid arguments to rgba, please pass multiple numbers e.g. rgb(255, 205, 100, 0.75) or an object e.g. rgb({ red: 255, green: 205, blue: 100, alpha: 0.75 }).")}var ce=function(e){return"number"==typeof e.red&&"number"==typeof e.green&&"number"==typeof e.blue&&("number"!=typeof e.alpha||void 0===e.alpha)},ue=function(e){return"number"==typeof e.red&&"number"==typeof e.green&&"number"==typeof e.blue&&"number"==typeof e.alpha},de=function(e){
return"number"==typeof e.hue&&"number"==typeof e.saturation&&"number"==typeof e.lightness&&("number"!=typeof e.alpha||void 0===e.alpha)},fe=function(e){return"number"==typeof e.hue&&"number"==typeof e.saturation&&"number"==typeof e.lightness&&"number"==typeof e.alpha},pe="Passed invalid argument to toColorString, please pass a RgbColor, RgbaColor, HslColor or HslaColor object."
function he(e){if("object"!=typeof e)throw new Error(pe)
if(ue(e))return se(e)
if(ce(e))return le(e)
if(fe(e))return oe(e)
if(de(e))return ie(e)
throw new Error(pe)}function me(e){return function t(n,a,r){return function(){var e=r.concat(Array.prototype.slice.call(arguments))
return e.length>=a?n.apply(this,e):t(n,a,e)}}(e,e.length,[])}function ve(e,t){var n=$(t)
return he(m({},n,{hue:(n.hue+parseFloat(e))%360}))}var ge=me(ve)
function ye(e){var t=$(e)
return he(m({},t,{hue:(t.hue+180)%360}))}function be(e,t,n){return Math.max(e,Math.min(t,n))}function Se(e,t){var n=$(t)
return he(m({},n,{lightness:be(0,1,n.lightness-parseFloat(e))}))}var we=me(Se)
function Ee(e,t){var n=$(t)
return he(m({},n,{saturation:be(0,1,n.saturation-parseFloat(e))}))}var ke=me(Ee)
function Ce(e){var n=Q(e),t=Object.keys(n).map(function(e){var t=n[e]/255
return t<=.03928?t/12.92:Math.pow((.055+t)/1.055,2.4)}),a=t[0],r=t[1],i=t[2]
return parseFloat((.2126*a+.7152*r+.0722*i).toFixed(3))}function xe(e){return he(m({},$(e),{saturation:0}))}function Te(e){var t=Q(e)
return he(m({},t,{red:255-t.red,green:255-t.green,blue:255-t.blue}))}function _e(e,t){var n=$(t)
return he(m({},n,{lightness:be(0,1,n.lightness+parseFloat(e))}))}var Me=me(_e)
function Pe(e,t,n){var a=Q(t),r=m({},a,{alpha:"number"==typeof a.alpha?a.alpha:1}),i=Q(n),o=m({},i,{alpha:"number"==typeof i.alpha?i.alpha:1}),l=r.alpha-o.alpha,s=2*parseFloat(e)-1,c=((s*l==-1?s:s+l)/(1+s*l)+1)/2,u=1-c
return se({red:Math.floor(r.red*c+o.red*u),green:Math.floor(r.green*c+o.green*u),blue:Math.floor(r.blue*c+o.blue*u),alpha:r.alpha+(o.alpha-r.alpha)*(parseFloat(e)/1)})}var Ie=me(Pe)
function Ne(e,t){var n=Q(t)
return se(m({},n,{alpha:be(0,1,(100*("number"==typeof n.alpha?n.alpha:1)+100*parseFloat(e))/100)}))}var Re=me(Ne)
function Le(e){return.179<Ce(e)?"#000":"#fff"}function je(e,t){var n=$(t)
return he(m({},n,{saturation:be(0,1,n.saturation+parseFloat(e))}))}var Ae=me(je)
function Be(e,t){return he(m({},$(t),{hue:parseFloat(e)}))}var De=me(Be)
function Oe(e,t){return he(m({},$(t),{lightness:parseFloat(e)}))}var Fe=me(Oe)
function qe(e,t){return he(m({},$(t),{saturation:parseFloat(e)}))}var We=me(qe)
function Ue(e,t){return Ie(parseFloat(e),"rgb(0, 0, 0)",t)}var ze=me(Ue)
function Ye(e,t){return Ie(parseFloat(e),"rgb(255, 255, 255)",t)}var He=me(Ye)
function Ve(e,t){var n=Q(t)
return se(m({},n,{alpha:be(0,1,(100*("number"==typeof n.alpha?n.alpha:1)-100*parseFloat(e))/100)}))}var Xe=me(Ve)
function Je(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
var a=Array.isArray(t[0])
if(!a&&8<t.length)throw new Error("The animation shorthand only takes 8 arguments. See the specification for more information: http://mdn.io/animation")
return{animation:t.map(function(e){if(a&&!Array.isArray(e)||!a&&Array.isArray(e))throw new Error("To pass multiple animations please supply them in arrays, e.g. animation(['rotate', '2s'], ['move', '1s'])\nTo pass a single animation please supply them in simple values, e.g. animation('rotate', '2s')")
if(Array.isArray(e)&&8<e.length)throw new Error("The animation shorthand arrays can only have 8 elements. See the specification for more information: http://mdn.io/animation")
return Array.isArray(e)?e.join(" "):e}).join(", ")}}function Ze(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return{backgroundImage:t.join(", ")}}function Ke(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return{background:t.join(", ")}}var Ge=["top","right","bottom","left"]
function Qe(e){for(var t=arguments.length,n=new Array(1<t?t-1:0),a=1;a<t;a++)n[a-1]=arguments[a]
var r
return"string"==typeof e&&0<=Ge.indexOf(e)?((r={})["border"+i(e)+"Width"]=n[0],r["border"+i(e)+"Style"]=n[1],r["border"+i(e)+"Color"]=n[2],r):(n.unshift(e),{borderWidth:n[0],borderStyle:n[1],borderColor:n[2]})}function $e(e,t){var n,a,r=i(e)
if(!t&&0!==t)throw new Error("borderRadius expects a radius value as a string or number as the second argument.")
if("Top"===r||"Bottom"===r)return(n={})["border"+r+"RightRadius"]=t,n["border"+r+"LeftRadius"]=t,n
if("Left"!==r&&"Right"!==r)throw new Error('borderRadius expects one of "top", "bottom", "left" or "right" as the first argument.')
return(a={})["borderTop"+r+"Radius"]=t,a["borderBottom"+r+"Radius"]=t,a}function et(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return r.apply(void 0,["borderStyle"].concat(t))}function tt(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return r.apply(void 0,["borderWidth"].concat(t))}function nt(e,t){return e(t?":"+t:"")}function at(e,t,n){if(!t)throw new Error("You must provide a template to this method.")
if(0===e.length)return nt(t,null)
for(var a=[],r=0;r<e.length;r+=1){if(n&&n.indexOf(e[r])<0)throw new Error("You passed an unsupported selector state to this method.")
a.push(nt(t,e[r]))}return a=a.join(",")}var rt=[void 0,null,"active","focus","hover"]
function it(e){return"button"+e+',\n  input[type="button"]'+e+',\n  input[type="reset"]'+e+',\n  input[type="submit"]'+e}function ot(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return at(t,it,rt)}function lt(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return r.apply(void 0,["margin"].concat(t))}function st(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return r.apply(void 0,["padding"].concat(t))}var ct=["absolute","fixed","relative","static","sticky"]
function ut(e){for(var t=arguments.length,n=new Array(1<t?t-1:0),a=1;a<t;a++)n[a-1]=arguments[a]
return 0<=ct.indexOf(e)?m({position:e},r.apply(void 0,[""].concat(n))):r.apply(void 0,["",e].concat(n))}function dt(e,t){return void 0===t&&(t=e),{height:e,width:t}}var ft=[void 0,null,"active","focus","hover"]
function pt(e){return'input[type="color"]'+e+',\n    input[type="date"]'+e+',\n    input[type="datetime"]'+e+',\n    input[type="datetime-local"]'+e+',\n    input[type="email"]'+e+',\n    input[type="month"]'+e+',\n    input[type="number"]'+e+',\n    input[type="password"]'+e+',\n    input[type="search"]'+e+',\n    input[type="tel"]'+e+',\n    input[type="text"]'+e+',\n    input[type="time"]'+e+',\n    input[type="url"]'+e+',\n    input[type="week"]'+e+",\n    input:not([type])"+e+",\n    textarea"+e}
function ht(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
return at(t,pt,ft)}function mt(){for(var e=arguments.length,t=new Array(e),n=0;n<e;n++)t[n]=arguments[n]
if(Array.isArray(t[0])&&2===t.length){var a=t[1]
if("string"!=typeof a)throw new Error("Property must be a string value.")
return{transition:t[0].map(function(e){return e+" "+a}).join(", ")}}return{transition:t.join(", ")}}},"/Mon":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledRightPane=void 0
var r=a(n("vOnD")).default.div.withConfig({displayName:"styles__StyledRightPane",componentId:"hqgthc-0"})(["position:relative;height:100%;transition:all 0.3s ease-in-out;z-index:100;.preview-panel-wrapper{position:absolute;top:0;left:0;height:100%;}"])
t.StyledRightPane=r},"/cyv":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:i,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"container:modal:open":return(0,r.default)({},a,{isOpen:!0})
case"container:modal:close":return(0,r.default)({},e,{isOpen:!1})}return e}
var r=a(n("MVZn")),i={isOpen:!1,type:"alert",alertType:"alert",title:"",desc:"",onClose:function(){return null},onCancel:null,onConfirm:null,cancelText:void 0,confirmText:void 0,canCancel:!0,canConfirm:!0,canClose:!0}},"/rSK":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.CommentMarker=void 0
var c=r(n("pVnL")),l=r(n("MVZn")),s=r(n("lwsE")),i=r(n("W8MJ")),u=r(n("a1gu")),d=r(n("Nsbk")),o=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),h=r(n("17x9")),m=r(n("vOnD")),v=n("fiFu"),g=function(e){function a(e){var r;(0,s.default)(this,a),r=(0,u.default)(this,(0,d.default)(a).call(this,e))
var i={isDragging:!1,position:{left:0,top:0}},t=(0,l.default)({},b,{mousemove:(0,v.muteEvent)(function(e){var t=r.props,n=t.commentThread,a=t.markerOperations.getMarkerPosition(e);(r.state.isDragging||function(e,t){var n=e.left-t.left,a=e.top-t.top
return S<=n*n+a*a}(n,a))&&r.setState({isDragging:!0,position:a})}),mouseup:(0,v.muteEvent)(function(e){if(o(),r.state.isDragging){var t=r.props,n=t.commentThread,a=t.markerOperations
a.doUpdateCommentThread((0,l.default)({cid:n.cid},a.getMarkerPosition(e)))}else setTimeout(function(){var e=r.props,t=e.isFocus,n=e.commentThread
e.markerOperations.setFocusCommentThreadCid(t?null:n.cid)},0)
r.setState(i)}),mouseleave:function(){o(),r.props.markerOperations.setHoverFocusCommentThreadCid(null),r.setState(i)}}),n=(0,l.default)({},b,{mouseup:t.mouseup}),o=function(){return r.props.markerOperations.removeContainerEventListener(r.props.isEditable?t:n)}
return r.markerListenerMap={onMouseDown:(0,v.muteEvent)(function(){return r.props.markerOperations.addContainerEventListener(r.props.isEditable?t:n)}),onMouseEnter:(0,v.muteEvent)(function(){return!r.props.isFocus&&r.props.markerOperations.setHoverFocusCommentThreadCid(r.props.commentThread.cid)}),onMouseLeave:(0,v.muteEvent)(function(){return r.props.isFocus&&r.props.markerOperations.setHoverFocusCommentThreadCid(null)}),onMouseUp:v.MUTE_EVENT,onDoubleClick:v.MUTE_EVENT,onClick:v.MUTE_EVENT},r.state=i,r}
return(0,o.default)(a,e),(0,i.default)(a,[{key:"render",value:function(){var e=this.props,t=e.commentThread,n=e.scale,a=e.isFocus,r=e.isFade,i=e.commentMarkerIndex,o=this.state,l=o.isDragging,s=o.position
return p.default.createElement(y,{className:a?"focus":!a&&r?"fade":"",style:{left:"".concat((l?s.left:t.left)*n,"px"),top:"".concat((l?s.top:t.top)*n,"px")}},p.default.createElement("span",(0,c.default)({tabIndex:i},this.markerListenerMap),i))}}]),a}(p.PureComponent)
t.CommentMarker=g,(0,f.default)(g,"propTypes",{commentMarkerIndex:h.default.number.isRequired,commentThread:h.default.object.isRequired,scale:h.default.number.isRequired,isEditable:h.default.bool,isFocus:h.default.bool,isFade:h.default.bool,markerOperations:h.default.object.isRequired})
var y=m.default.div.withConfig({displayName:"CommentMarkerPanelMarker__CommentMarkerDiv",componentId:"kuapf2-0"})(["position:absolute;width:","px;height:","px;overflow:visible;& > span{display:flex;justify-content:center;align-items:center;cursor:pointer;outline:none;margin-left:","px;margin-top:","px;width:","px;height:","px;font-size:14px;line-height:",
"px;box-shadow:0 2px 10px rgba(108,0,0,0.22);border:2px solid #fff;border-radius:100%;background:#ff7100;color:#fbfbfc;transition:all 0.1s ease-in;transform:scale(1);}&.focus > span{transform:scale(1.21);}&.fade > span{opacity:0.5;}"],0,0,-14,-14,28,28,28),b={mouseup:v.MUTE_EVENT,mousedown:v.MUTE_EVENT,mousemove:v.MUTE_EVENT,mouseleave:v.MUTE_EVENT,mouseout:v.MUTE_EVENT,click:v.MUTE_EVENT,dblclick:v.MUTE_EVENT},S=225},"0uCA":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=a(n("lwsE")),r=a(n("W8MJ")),l=a(n("a1gu")),s=a(n("Nsbk")),c=a(n("PJYZ")),u=a(n("7W2i")),d=a(n("lSNA")),f=a(n("q1tI")),i=a(n("17x9")),p=n("1qiG"),h=function(e){function i(){var e,r;(0,o.default)(this,i)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return r=(0,l.default)(this,(e=(0,s.default)(i)).call.apply(e,[this].concat(n))),(0,d.default)((0,c.default)(r),"genLines",function(e,t){var n=r.props.style,a=[]
return 0<e.top&&a.push(f.default.createElement("div",{key:"top",className:"line top",style:{borderTopStyle:"".concat(n.dashed?"dashed":"solid"),borderTopColor:n.colorForLines,top:(0,p.toPercentage)(e.top/t.height)}})),e.left+e.width<t.width&&a.push(f.default.createElement("div",{key:"right",className:"line right",style:{borderLeftStyle:"".concat(n.dashed?"dashed":"solid"),borderLeftColor:n.colorForLines,left:(0,p.toPercentage)((e.left+e.width)/t.width)}})),e.top+e.height<t.height&&a.push(
f.default.createElement("div",{key:"bottom",className:"line bottom",style:{borderTopStyle:"".concat(n.dashed?"dashed":"solid"),borderTopColor:n.colorForLines,top:(0,p.toPercentage)((e.top+e.height)/t.height)}})),0<e.left&&a.push(f.default.createElement("div",{key:"left",className:"line left",style:{borderLeftStyle:"".concat(n.dashed?"dashed":"solid"),borderLeftColor:n.colorForLines,left:(0,p.toPercentage)(e.left/t.width)}})),a}),r}return(0,u.default)(i,e),(0,r.default)(i,[{key:"render",value:function(){
var e=this.props,t=e.refRect,n=e.screen
return f.default.createElement("div",{className:"verbose-auxiliary-lines"},this.genLines(t,n))}}]),i}(f.default.Component);(t.default=h).propTypes={refRect:i.default.object,screen:i.default.object,style:i.default.object}},"18l9":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=n("G4qV"),o=n("upRB"),l=n("1iCU"),s=n("pVAx"),c=a(n("tRkt")),u=(0,i.createSelector)([o.getPreference,o.getCurrentMode,o.getIsMultiScreenProject],function(e,t,n){return{toolbarActiveItem:t,isScreenPanelShow:e.layout===s.CLASSIC&&n,isLayerPanelShow:e.layout!==s.CLASSIC&&t===l.INSPECT,isCommentPanelShow:e.layout!==s.CLASSIC&&t==l.COMMENT}}),d=(0,r.connect)(function(e){return u(e)})(c.default)
t.default=d},"1gVK":function(e,t,n){"use strict"
var a,r=n("TqRt")(n("cDf5"));(a="undefined"!=typeof window?window:void 0).Shake=function(i,n){function e(e){if(this.hasDeviceMotion="ondevicemotion"in i,this.options={threshold:15,timeout:1e3},"object"===(0,r.default)(e))for(var t in e)e.hasOwnProperty(t)&&(this.options[t]=e[t])
if(this.lastTime=new Date,this.lastX=null,this.lastY=null,this.lastZ=null,"function"==typeof n.CustomEvent)this.event=new n.CustomEvent("shake",{bubbles:!0,cancelable:!0})
else{if("function"!=typeof n.createEvent)return!1
this.event=n.createEvent("Event"),this.event.initEvent("shake",!0,!0)}}return e.prototype.reset=function(){this.lastTime=new Date,this.lastX=null,this.lastY=null,this.lastZ=null},e.prototype.start=function(){this.reset(),this.hasDeviceMotion&&i.addEventListener("devicemotion",this,!1)},e.prototype.stop=function(){this.hasDeviceMotion&&i.removeEventListener("devicemotion",this,!1),this.reset()},e.prototype.devicemotion=function(e){var t=e.accelerationIncludingGravity
if(t){var n,a,r
if(null===this.lastX&&null===this.lastY&&null===this.lastZ)return this.lastX=t.x,this.lastY=t.y,void(this.lastZ=t.z)
n=Math.abs(this.lastX-t.x),a=Math.abs(this.lastY-t.y),r=Math.abs(this.lastZ-t.z),(n>this.options.threshold&&a>this.options.threshold||n>this.options.threshold&&r>this.options.threshold||a>this.options.threshold&&r>this.options.threshold)&&(new Date).getTime()-this.lastTime.getTime()>this.options.timeout&&(i.dispatchEvent(this.event),this.lastTime=new Date),this.lastX=t.x,this.lastY=t.y,this.lastZ=t.z}},e.prototype.handleEvent=function(e){if("function"==typeof this[e.type])return this[e.type](e)},e}(a,
a.document)},"1qiG":function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.toPercentage=t.getDistancesForDirections=void 0
var s=n("ZXhj")
t.getDistancesForDirections=function(e,t){if((0,s.checkIfTwoRectsOverlap)(e,t))return{top:e.top-t.top,right:t.left+t.width-(e.left+e.width),bottom:t.top+t.height-(e.top+e.height),left:e.left-t.left}
var n={},a=function(e,t){var n=[],a=(0,s.getMinContainingRect)(e,t)
if(a.width<e.width+t.width)n[0]=null
else{var r=a.width-(e.width+t.width),i=t.left>e.left
n[0]=i?r:-r}if(a.height<e.height+t.height)n[1]=null
else{var o=a.height-(e.height+t.height),l=t.top>e.top
n[1]=l?o:-o}return n}(e,t)
return 0<a[0]?n.right=a[0]:a[0]<0&&(n.left=Math.abs(a[0])),0<a[1]?n.bottom=a[1]:a[1]<0&&(n.top=Math.abs(a[1])),n}
t.toPercentage=function(e){return"".concat(100*e,"%")}},"20hc":function(e,t,n){"use strict"
var a=n("TqRt"),m=a(n("o0o1")),r=a(n("yXPU")),v=a(n("q1tI")),g=a(n("i8i4")),o=n("XkTy"),i=n("tajm"),l=n("tQ2B"),s=n("t3Un"),y=a(n("NkXT")),c=a(n("dYO+")),u=a(n("udLg")),d=window,b=d.$,S=d.MB,f=d.md5
S.f.inSharing=!0
var w=function(){return window.MBData}
S.load=function(){var t=(0,r.default)(m.default.mark(function e(n){var a,r,i,o,l,s,c,u,d,f,p,h
return m.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(a=n.projectAccessToken,r=n.projectEncryptedPassword,i=n.projectName,o=n.projectIconUrl,l=n.projectUpdatedAt,s=n.isPasswordRequired,c=n.isProjectExportable,u=n.urlClientIOS,d=n.urlClientAndroid,S.webpackInterface.renderPreviewAlert(),S.supportedBrowser()){e.next=6
break}return b("#splash").hide(),b("#loading").hide(),e.abrupt("return")
case 6:return f=S.isMac()?"mac":S.isWindows()?"windows":"other-os",b("html").addClass(f),(S.isStandAlone()||S.isIOSClient())&&b("html").addClass("is-full-screen"),p=void 0,r=r||new URLSearchParams(location.search).get("password")||(t=a,S.localStorageDelegate.getItem("".concat(t,"_pwd"))),e.next=13,E(s,a,r)
case 13:if(e.t0=e.sent,e.t0){e.next=16
break}e.t0=[]
case 16:if(h=e.t0,p=h[0],r=h[1],p){e.next=21
break}return e.abrupt("return")
case 21:if(!S.isMobile()||S.isInApp||S.isStandAlone()||w()||S.isEmbedded()){e.next=24
break}return e.next=24,new Promise(function(e){b("#loading").hide(),g.default.render(v.default.createElement(y.default,{projectAccessToken:a,projectEncryptedPassword:r,projectName:i,projectIconUrl:o,projectUpdatedAt:l,isProjectExportable:c,urlClientIOS:u,urlClientAndroid:d,loadProject:e}),document.getElementById("workspace"))})
case 24:b(".indicator").css("height","100%"),setTimeout(function(){return k(p)},300)
case 26:case"end":return e.stop()}var t},e)}))
return function(e){return t.apply(this,arguments)}}()
var E=function(){var a=(0,r.default)(m.default.mark(function e(t,n,a){var r,i
return m.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,p(n,a)
case 2:if((r=e.sent)||t){e.next=6
break}return(0,o.alertAsync)({desc:I18N.no_permission_to_app}),e.abrupt("return")
case 6:i=1/0
case 7:if(!r&&i)return i--,e.t0=f,e.next=12,(0,o.promptGetPasswordAsync)()
e.next=19
break
case 12:return e.t1=e.sent,a=(0,e.t0)(e.t1),e.next=16,p(n,a)
case 16:r=e.sent,e.next=7
break
case 19:if(r){e.next=23
break}return console.log("Failed prompt password, again"),setTimeout(function(){return(0,o.alertAsync)({desc:t?I18N.invalid_credential:"Failed to load this app."})},320),e.abrupt("return")
case 23:return e.abrupt("return",[r,a])
case 24:case"end":return e.stop()}},e)}))
return function(e,t,n){return a.apply(this,arguments)}}()
S.renderEmbedShell=function(e){var t=e.project,n=e.shellType,a=e.isLandscape
g.default.render(v.default.createElement(c.default,{project:t,shellType:n,isLandscape:a}),document.getElementById("project-shell"))}
var p=function(){var n=(0,r.default)(m.default.mark(function e(r,i){var o
return m.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(e.prev=0,!w()){e.next=5
break}e.t0=h(i),e.next=8
break
case 5:return e.next=7,(0,s.requestJSON)("/app/".concat(r,".json").concat(i?"?password=".concat(i):""))
case 7:e.t0=e.sent
case 8:return o=e.t0,n=r,a=i,S.localStorageDelegate.setItem("".concat(n,"_pwd"),a),e.abrupt("return",o)
case 13:e.prev=13,e.t1=e.catch(0),console.log("[getProjectFullData] failed: ".concat(e.t1)),t=r,S.localStorageDelegate.removeItem("".concat(t,"_pwd"))
case 17:case"end":return e.stop()}var t,n,a},e,null,[[0,13]])}))
return function(e,t){return n.apply(this,arguments)}}(),h=function(e){var t=w(),n=t.project.password
if(n&&n!==e)throw new Error("[offline] password mismatch")
return t},k=function(e){var t=e.org,n=e.team,a=(0,l.refreshProjectFullData)(e)
S.isEmbedded()||(0,l.refreshMessagePreferenceData)(S.preferenceData),S.currentOrg=t,S.currentTeam=n,S.currentProject=a,S.isMobile()||S.isEmbedded()||(0,i.patchGlobalAutoSaverPusher)(),b("title").html(a.name),b("#loading").hide(),!a.validated&&S.isMobile()&&(0,o.alertAsync)({title:I18N.reminder,desc:I18N.fraud_warning,confirmText:I18N.fraud_confirm,isHTML:!0}),S.checkFA(function(){S.webpackInterface.init(),S.Pusher&&S.user.id&&"guest"!==S.webpackInterface.store.getState(
).model.current.userRole&&S.Pusher.enableSocketChannel(a.cid)
var e=location.hash||"",t=e&&e.startsWith("#screen=")&&e.substr("#screen=".length),n=Screen.find(t)||a.homeScreen()
b("body").data("scale",100),(S.isMobile()||S.isEmbedded())&&(a.scale=100,a.lsave(!1)),S.currentProject=a,S.currentScreen=n,S.runner=new u.default,S.webpackInterface.renderPreview(document.querySelector("#workspace")),setTimeout(function(){b("#workspace").show(),S.runner.init(a,n)},100)})}},"2AqR":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=a(n("H27A")),l=n("upRB"),o=(0,r.connect)(function(e){var t=e.container,n=t.common.scale,a=t.previewSetting,r=a.toolbarActiveItem,i=a.loadSliceUrl,o=(0,l.getPreference)(e).show_toolbar_text
return{scale:n,project:(0,l.getCurrentProject)(e),toolbarActiveItem:r,loadSliceUrl:i,isScrollable:(0,l.getIsScrollable)(e),isHighlight:(0,l.getIsHighlight)(e),isStickyShow:(0,l.getIsStickyShow)(e),shellType:(0,l.getShellType)(e),showToolBarText:o}})(i.default)
t.default=o},"2M3O":function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.requestSnapshotZip=t.requestSnapshot=t.requestThumbnail=void 0
var a=n("SVae"),r=n("3ceZ")
t.requestThumbnail=function(e){return((0,r.isPublicScreenAvailable)(e)?r.requestThumbnailPublic:a.requestThumbnailLocalhost)(e)}
t.requestSnapshot=function(e){return((0,r.isPublicScreenAvailable)(e)?r.requestSnapshotPublic:a.requestSnapshotLocalhost)(e)}
t.requestSnapshotZip=function(e){return((0,r.isPublicProjectAvailable)(e)?r.requestSnapshotZipPublic:a.requestSnapshotZipLocalhost)(e)}},"2b0G":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),d=r(n("17x9")),f=a(n("q1tI")),p=n("6XO9")
n("mxnB")
var h=function(e){function t(){return(0,i.default)(this,t),(0,l.default)(this,(0,s.default)(t).apply(this,arguments))}return(0,c.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){return f.default.createElement(f.default.Fragment,null,f.default.createElement("span",{className:"last-screen","data-action":"last",onClick:this.props.onClick},f.default.createElement(p.SVG,{className:"left-arrow",name:"angle_bracket_left"})),f.default.createElement("span",{className:"next-screen","data-action":"next",
onClick:this.props.onClick},f.default.createElement(p.SVG,{className:"right-arrow",name:"angle_bracket_right"})))}}]),t}(f.PureComponent)
t.default=h,(0,u.default)(h,"propTypes",{onClick:d.default.func})},"2eJi":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.entryMap=void 0
var y=a(n("J4zp")),r=a(n("MVZn")),o=a(n("zkrS")),b=n("upRB"),i=n("6UMJ"),l=n("CWx7"),s=n("4daP"),S=n("Gbs1"),c=n("rbsZ"),u=n("1iCU"),d=n("oose"),f=(0,r.default)({},i.keyEntry,l.runnerEntry,s.playSettingEntry,{"entry:init:preview:related:data":function(e){var t=e.dispatch
t({type:"preview:update:state",payload:{preference:MB.preference()}}),t({type:"entry:refresh:project-related"})},"entry:preview:select":function(e,t){var n=e.dispatch,a=e.getState,r=t.payload.toolbarActiveItem
if(r!=a().container.previewSetting.toolbarActiveItem){if(r===u.INSPECT)n({type:"SET_VISIBILITY_SCREEN",payload:{screenID:o.default.MB.currentScreen?o.default.MB.currentScreen.cid:-1}})
else if(r===u.COMMENT){var i=(0,d.getProjectAllowCommentStatus)(o.default.MB.currentProject)
"deny_limitation"===i&&(0,c.openRenewModal)("comment_".concat(i),{action:"comment_".concat(i),renewRedirectParams:o.default.MB.currentProject.team_cid||o.default.MB.currentProject.owner_id===o.default.MB.user.id?{access_token:o.default.MB.currentProject.access_token}:null})}n({type:"reducer:preview-toolbar:update",payload:{toolbarActiveItem:r}}),setTimeout(function(){(0,b.getRunnerActiveScreenCid)(a())&&o.default.MB.runner.reload()})}},"entry:init:preview:scale":function(e){var t=e.getState,n=e.dispatch,
a=t(),r=(0,b.getCurrentProject)(a)
if(MB.isUIChina()&&"car_play"===r.model)n({type:"preview:set:scale",payload:{scale:40}})
else{var i=function(e){return Number(MB.localStorageDelegate.getItem("preview_scale_".concat(e)))}(r.cid)
i&&!MB.isForum()?n({type:"preview:set:scale",payload:{scale:i}}):n({type:"entry:auto-fit:preview:scale"})}},"entry:auto-fit:preview:scale":function(e){var t=e.getState,n=e.dispatch,a=t(),r=a.container.previewSetting.isFullScreenMode,i=(0,b.getCurrentProject)(a),o=(0,b.getCurrentScreen)(a),l=(0,b.getShellType)(a),s=(0,S.getProjectShell)(i,l),c="landscape"===o.orientation?[s.height,s.width]:[s.width,s.height],u=(0,y.default)(c,2),d=u[0],f=u[1],p=i.template?.8:1,h=r||MB.isForum()?0:500,m=window.innerWidth*p-h,
v=window.innerHeight*p-56,g=100*Math.min((v-40)/f,(m-40)/d)
n({type:"preview:set:scale",payload:{scale:Math.min(Math.max(g,20),100)}})},"entry:preview:set:scale":function(e,t){var n=e.dispatch,a=e.getState,r=t.payload.scale,i=a(),o=i.model.current.projectCid
!i.container.previewSetting.isFullScreenMode&&function(e,t){MB.localStorageDelegate.setItem("preview_scale_".concat(e),t)}(o,r),n({type:"preview:set:scale",payload:{scale:r}})},"entry:preview:set:canvas:offset":function(e,t){var n=e.getState,a=e.dispatch,r=t.payload.offset,i=n(),o=(0,b.getCurrentScreen)(i),l=(0,b.getCurrentScale)(i),s=document.querySelector("#preview_scrollBar_viewport").getBoundingClientRect(),c=s.width,u=s.height,d=Math.max(3.5*c,o.width*l/100*2),f=Math.max(3.5*u,o.height*l/100*2),p=r.x,
h=r.y
a({type:"preview:set:canvas:offset",payload:{offset:{x:p=-Math.max(Math.min(-p,d/2),-d/2),y:h=-Math.max(Math.min(-h,f/2),-f/2)}}})},"entry:enter:full-screen-mode":function(e){var t=e.dispatch
MB.event("preview","工具栏: 全屏模式开启"),t({type:"entry:preview:select",payload:{toolbarActiveItem:"preview"}}),t({type:"reducer:preview-toolbar:fullscreen",payload:{isFullScreenMode:!0}}),t({type:"entry:auto-fit:preview:scale"}),t({type:"preview:set:canvas:offset",payload:{offset:{x:0,y:-28}}})},"entry:exit:fill-screen-mode":function(e){var t=e.dispatch
MB.event("preview","工具栏: 全屏模式关闭"),t({type:"reducer:preview-toolbar:fullscreen",payload:{isFullScreenMode:!1}}),t({type:"entry:init:preview:scale"}),t({type:"preview:set:canvas:offset",payload:{offset:{x:0,y:0}}})}})
t.entryMap=f},"2s0x":function(e,t,n){e.exports={"slice-container":"_2FLjTBOWTdJe3M3sw-VdYI","slice-load-wrap":"_3KRRSNQeMq8ecSlOMYMVeF","slice-item":"_33HowBUzwgAHj2ZrVfoG3D",active:"oKXaiboaXdf8OtZ5FC5BI",download:"_1fom5UBbirvQ9gHFIkoaaz","icon-download":"_1bkbkk-E2IExD0mLX66FYn","no-slice":"_2lJKTFDIEz2pCYIaVad38l",spinner:"_3_b065M_IA1bQOZX-cJx3-","rotate-infinite":"pHICLqPtUNQ0NhVXRboiI","download-slice-load":"_2VjpVdYeSW_HDEeGZ3M2DG"}},"3caq":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.createWorkspacePusher=void 0
var S=a(n("o0o1")),g=a(n("yXPU")),y=a(n("MVZn")),w=n("Saem"),E=n("Clcl"),k=n("RrAf"),f=n("qYFl"),C=window.MB
t.createWorkspacePusher=function(e){var t,n,a=e.filterStaleData,b=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:[],o=h(),t=e.reduce(function(e,t){var n=t.object,a=n.cid,r=n.mtime,i=void 0===r?o:r
return e[a]=i,e},{})
return a(t)},r=(0,y.default)({},k.initialSocketState,{userId:C.user.id,projectCidList:[]}),i={"broadcast:user:data":function(e){e.type
var t=e.payload,n=b(t).remoteStaleCidSet,a=!0,r=!1,i=void 0
try{for(var o,l=t[Symbol.iterator]();!(a=(o=l.next()).done);a=!0){var s=o.value,c=s.action,u=s.className,d=s.object
x(n,u,c,d)}}catch(e){r=!0,i=e}finally{try{a||null==l.return||l.return()}finally{if(r)throw i}}},"broadcast:upgrade-notice:new":function(e){e.type
var t=e.payload.target_users,n=["pro","mockingbot.com","mockingbot.in"].some(function(e){return location.hostname.includes(e)})?"pro":"free"
"free"===t&&"pro"==n||"pro"===t&&"free"==n||C.action("entry:update:upgrade-notice-indicator-status",{status:"TWINKLE"})}},o={"broadcast:project:data":(n=(0,g.default)(S.default.mark(function e(t){var n,a,r,i,o,l,s,c,u,d,f,p,h
return S.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:t.type,n=t.payload,a=b(n),r=a.remoteStaleCidSet,o=!(i=!0),l=void 0,e.prev=6,s=n[Symbol.iterator]()
case 8:if(i=(c=s.next()).done){e.next=15
break}return u=c.value,d=u.action,f=u.className,p=u.object,h=u.extraInfo,e.next=12,T(r,f,d,p,h)
case 12:i=!0,e.next=8
break
case 15:e.next=21
break
case 17:e.prev=17,e.t0=e.catch(6),o=!0,l=e.t0
case 21:e.prev=21,e.prev=22,i||null==s.return||s.return()
case 24:if(e.prev=24,o)throw l
e.next=27
break
case 27:return e.finish(24)
case 28:return e.finish(21)
case 29:case"end":return e.stop()}},e,null,[[6,17,21,29],[22,,24,28]])})),function(e){return n.apply(this,arguments)}),"broadcast:project:batch-save":(t=(0,g.default)(S.default.mark(function e(t){var n,a,r,i,o,l,s,c,u,d,f,p,h,m,v,g,y
return S.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:t.type,n=t.payload,a=n.fromUser,r=n.rootProjectCid,i=n.batchSaveQueue,o=(void 0===i?[]:i).map(function(e){var t=e.method,n=e.body,a=e.extraInfo
return{className:a.className,action:"PUT"===t?"update":"DELETE"===t?"destroy":"POST"===t?"create":"",object:n?JSON.parse(n):{cid:a.cid},extraInfo:a}}),l=b(o),s=l.remoteStaleCidSet,u=!(c=!0),d=void 0,e.prev=7,f=o[Symbol.iterator]()
case 9:if(c=(p=f.next()).done){e.next=16
break}return h=p.value,m=h.className,v=h.action,g=h.object,y=h.extraInfo,e.next=13,T(s,m,v,g,y,r,a)
case 13:c=!0,e.next=9
break
case 16:e.next=22
break
case 18:e.prev=18,e.t0=e.catch(7),u=!0,d=e.t0
case 22:e.prev=22,e.prev=23,c||null==f.return||f.return()
case 25:if(e.prev=25,u)throw d
e.next=28
break
case 28:return e.finish(25)
case 29:return e.finish(22)
case 30:case"end":return e.stop()}},e,null,[[7,18,22,30],[23,,25,29]])})),function(e){return t.apply(this,arguments)})},l=(0,k.createSocketStore)({initialState:r,socketPayloadListenerMap:i,socketPayloadQueueAsyncListenerMap:o}),s=l.getState,c=l.setState,u=l.addEventListener,d=l.removeEventListener,f=l.destroy,p=l.getIsSocketConnected,h=l.getSocketTimestamp,m=l.sendSocketPayloadAsync
u("socket:open",function(){var e=s().projectCidList
e.length&&m("join:projects",{projectCidList:e}).catch(E.REPORT_ERROR)})
var v=function(){var t=(0,g.default)(S.default.mark(function e(t){var n,a
return S.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=s(),a=n.projectCidList,e.abrupt("return",!a.includes(t)&&m("join:projects",{projectCidList:[t]}).then(function(e){c({projectCidList:(0,w.arrayMatchPush)(a,t)})},E.REPORT_ERROR))
case 2:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
return{addEventListener:u,removeEventListener:d,destroy:f,getIsSocketConnected:p,getSocketTimestamp:h,joinProject:v,leaveProject:function(t){var n=s().projectCidList
return n.includes(t)&&m("leave:projects",{projectCidList:[t]}).then(function(e){c({projectCidList:(0,w.arrayMatchDelete)(n,t)})},E.REPORT_ERROR)},requestBatchSave:function(e){var t=e.batchSaveQueue,n=void 0===t?[]:t,a=e.rootProjectCid,r=void 0===a?"":a,i=e.fromUser
return m("request:project:batch-save",{batchSaveQueue:n,rootProjectCid:r,fromUser:void 0===i?{}:i})},enableSocketChannel:v,resetSocketChannel:function(){var e=s().projectCidList
return m("leave:projects",{projectCidList:e}).then(function(e){c({projectCidList:[]})},E.REPORT_ERROR)}}}
var x=function(e,t,n,a){e.has(a.cid)||(0,f.isRemoteMtimeStale)(t,a.cid,a.mtime)||("Team"===t?(0,f.updateTeam)(n,a):"Project"===t?(0,f.updateProject)(n,a):"Collaborator"===t&&(0,f.updateCollaborator)(n,a))},T=function(){var o=(0,g.default)(S.default.mark(function e(t,n,a,r,i,o){var l,s,c,u,d=arguments
return S.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(l=6<d.length&&void 0!==d[6]?d[6]:{},t.has(r.cid)||(0,f.isRemoteMtimeStale)(n,r.cid,r.mtime))return e.abrupt("return")
e.next=3
break
case 3:if("Asset"===n)return e.abrupt("return",(0,f.updateAsset)(a,r))
e.next=5
break
case 5:if("PointComments::Comment"===n||"Comment"===n)return e.abrupt("return",C.webpackInterface&&C.webpackInterface.pushData("comments",a,r))
e.next=7
break
case 7:if("PointComments::Thread"===n||"CommentThread"===n)return e.abrupt("return",C.webpackInterface&&C.webpackInterface.pushData("comment-threads",a,r))
e.next=9
break
case 9:if(C.f.inSharing||!C.currentProject)return e.abrupt("return")
e.next=11
break
case 11:if(e.t0=f.updateWorkspaceMap[n],e.t0)return e.next=15,f.updateWorkspaceMap[n](a,r,i)
e.next=15
break
case 15:l.id&&(!(s="Screen"===n?r.cid:r.screen_cid)&&r.screenstate_cid&&(c=Screenstate.find(r.screenstate_cid))&&(s=c.screen_cid),(u=CoWorker.find(l.id)||new CoWorker({cid:l.id,name:l.name,avatar:l.avatar})).screen_cid=s,u.last_seen=new Date,u.save(),C.renderCoWorkers&&C.renderCoWorkers())
case 16:case"end":return e.stop()}},e)}))
return function(e,t,n,a,r,i){return o.apply(this,arguments)}}()},"3ceZ":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.requestSnapshotZipPublic=t.requestSnapshotPublic=t.requestThumbnailPublic=t.isPublicScreenAvailable=t.isPublicProjectAvailable=void 0
var f=a(n("MVZn")),p=a(n("J4zp")),m=a(n("o0o1")),r=a(n("yXPU")),v=a(n("zkrS")),i=n("r2i6"),g=n("/N2d"),h=n("CpT9"),o=window.location,y="".concat(o.origin,"/api/v2/snapshots/public"),b=function(){return window.MB_DESKTOP_SNAPSHOT||window.parent.MB_DESKTOP_SNAPSHOT},l=function(e){return"function"==typeof b()&&e.projectAccessToken&&v.default.SpineModel.Project.findAllByAttribute("access_token",e.projectAccessToken)}
t.isPublicProjectAvailable=l
t.isPublicScreenAvailable=function(e){return l(e)&&e.screenCid&&v.default.SpineModel.Screen.find(e.screenCid)}
var S=(0,i.createCacheMap)({valueSizeSumMax:8388608,valueSizeSingleMax:1048576}),s=function(){var t=(0,r.default)(m.default.mark(function e(t){var n,a,r,i,o,l,s,c,u,d,f,p,h
return m.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(n=t.imageElement,t.projectAccessToken,a=t.screenCid,r=t.screenStateCid,i=void 0===r?"default":r,o=t.mode,void 0===o?"thumbnail":o,l=t.version,s=void 0===l?"":l,e.prev=1,u=v.default.SpineModel.Screen.find(a),d=128/Math.max(u.width,u.height),f="".concat(a,"|").concat(i,"|").concat(d),void 0===(c=S.get("".concat(f,"|").concat(s))))return e.next=9,b()({snapshotMode:"png-base64",snapshotUrl:y,taskList:[(0,g.doRenderScreenToHTMLString)({
screenCid:a,screenStateCid:i,canvasZoom:d})]})
e.next=13
break
case 9:p=e.sent,h=p.imageBase64PNGMap,c=h[f],S.set("".concat(f,"|").concat(s),c,c.length,Date.now()+6e4)
case 13:e.next=18
break
case 15:e.prev=15,e.t0=e.catch(1)
case 18:return n.src=c||"/images/preview/image-load.png",e.abrupt("return",n)
case 20:case"end":return e.stop()}},e,null,[[1,15]])}))
return function(e){return t.apply(this,arguments)}}()
t.requestThumbnailPublic=s
var c=function(){var t=(0,r.default)(m.default.mark(function e(t){var n,a,r,i,o,l
return m.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return t.projectAccessToken,n=t.screenCid,a=t.canvasZoom,r=void 0===a?1:a,i=v.default.SpineModel.Screen.find(n),e.next=5,b()({snapshotMode:"png-file",snapshotUrl:y,snapshotOutputFile:"".concat((0,h.getScreenFileName)(i),".png"),taskList:[(0,g.doRenderScreenToHTMLString)({screenCid:n,screenStateCid:"default",canvasZoom:r})]})
case 5:return o=e.sent,l=o.fileOutput,e.abrupt("return",{fileOutput:l,path:"#"})
case 8:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.requestSnapshotPublic=c
var u=function(){var t=(0,r.default)(m.default.mark(function e(t){var n,a,r,i,o,l,s,c,u,d
return m.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.projectAccessToken,a=t.canvasZoom,r=void 0===a?1:a,i=t.onProgress,o=v.default.SpineModel.Project.findAllByAttribute("access_token",n),l=(0,p.default)(o,1),s=l[0],c=v.default.SpineModel.Screen.findAllByAttribute("project_cid",s.cid),e.next=5,b()({snapshotMode:"png-zip-file",snapshotUrl:y,snapshotOutputFile:"".concat(s.name,".zip"),taskList:c.map(function(e){return(0,f.default)({},(0,g.doRenderScreenToHTMLString)({
screenCid:e.cid,screenStateCid:"default",canvasZoom:r}),{zipPath:"".concat(s.name,"_").concat(s.timestamp,"/").concat((0,h.getScreenFileName)(e),".png")})}),onProgress:i})
case 5:return u=e.sent,d=u.fileOutput,e.abrupt("return",{fileOutput:d,path:"#"})
case 8:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.requestSnapshotZipPublic=u},"3xeE":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.CommentLayer=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=a(n("q1tI")),p=r(n("17x9")),h=r(n("vOnD")),m=n("+IKJ"),v=n("6XO9"),g=r(n("zkrS")),y=n("FC/4"),b=n("3xoc"),S=n("U9kS"),w=n("fiFu"),E=g.default.MB,k=g.default.I18N,C=function(e){function t(e){var r;(0,i.default)(this,t),r=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(r),"renderContentReply",function(){var e=r.props.permissionPack.userAuthStatus,t=r.state.isValidReply
return f.default.createElement("div",{className:"reply-footer"},e===w.USER_AUTH_STATUS_MEMBER&&f.default.createElement(y.TextEditComponent,{textEditStore:r.replyStore,placeholder:k.preview.comment.comment_placeholder,minHeight:20,autoHeight:!0,multiline:!0}),e===w.USER_AUTH_STATUS_MEMBER&&(0,b.getDarkerButton)(k.preview.comment.thread_create,function(){E.event("zhuge","Comment_Add_Comment"),r.replyStore.endEdit()},!t),e===w.USER_AUTH_STATUS_NOT_SIGN_IN&&f.default.createElement(v.CoreButton,{onClick:T},
k.preview.comment.tip_signin),e===w.USER_AUTH_STATUS_NOT_MEMBER&&f.default.createElement("span",null,k.preview.comment.tip_not_collaborator))})
return r.commentOperations={getPermission:function(e){return r.props.permissionPack.getPermission(e)},getUserProfile:function(e){return r.props.getUserProfile(e)},setHoverFocusCommentThreadCid:function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:null
return!r.props.tempCommentThreadMarker&&function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:null
return r.props.focusCommentThreadCid!==e&&r.props.dispatch({type:"container:comment:focus",payload:{focusCommentThreadCid:e,focusSource:"panel"}})}(e)},doDeleteCommentThread:function(e){return r.props.dispatch({type:"entry:comment-threads:delete",payload:{cid:e}})},doDeleteComment:function(e){return r.props.dispatch({type:"comments:delete",payload:e})},doUpdateComment:function(e){return r.props.dispatch({type:"entry:comments:update",payload:e})},doCreateComment:function(e,t){return e&&r.props.dispatch({
type:"entry:comments:add",payload:{thread_cid:t,message:e}})}},r.doCreateCommentThread=function(e){var t=r.props.tempCommentThreadMarker||{top:0,left:0},n=t.left,a=t.top
e&&r.props.dispatch({type:"entry:comment-threads:add",payload:{top:a,left:n,message:e}}),setTimeout(function(){r.scrollRef&&(r.scrollRef.scrollTop=r.scrollRef.scrollHeight-r.scrollRef.offsetHeight)},0)},r.replyStore=(0,y.createTextEditStore)({isEditing:!0},{onChange:function(e){var t=e.value
return r.setState({isValidReply:Boolean(t)})},onEnd:function(e){var t=e.value,n=void 0===t?"":t
r.doCreateCommentThread(n.trim()),r.resetReply()}}),r.resetReply=function(){r.replyStore.startEdit(),r.replyStore.setValue(""),r.setState({isValidReply:!1})},r.focusReply=function(){r.replyStore.endEdit(),r.replyStore.startEdit()},r.setScrollRef=function(e){r.scrollRef=e},r.scrollRef=null,r.state={isValidReply:!1},r}return(0,u.default)(t,e),(0,o.default)(t,[{key:"componentDidMount",value:function(){!this.props.isLoaded&&this.props.dispatch({type:"entry:comment:init-project-data"}),E.AutoSaver&&(
this.prevAutoSaverDelay=E.AutoSaver.getDelay(),E.AutoSaver.setDelay(500))}},{key:"componentDidUpdate",value:function(e){this.props.tempCommentThreadMarker&&!e.tempCommentThreadMarker&&this.focusReply()}},{key:"componentWillUnmount",value:function(){E.AutoSaver&&E.AutoSaver.setDelay(this.prevAutoSaverDelay)}},{key:"render",value:function(){var o=this,e=this.props,t=e.screenName,n=e.commentThreadList,l=e.commentListMap,a=e.permissionPack,r=e.isLoaded,i=e.focusCommentThreadCid,s=e.focusSource,
c=e.tempCommentThreadMarker
if(!r)return f.default.createElement(x,null)
var u=i||c&&c.cid,d=0!==n.length
return f.default.createElement(x,null,d&&f.default.createElement("div",{className:"comment-title"},"".concat(t," (").concat(n.length,")")),d&&f.default.createElement("div",{ref:this.setScrollRef,className:"comment-thread"},n.map(function(e,t){var n=l[e.cid]||[],a=t+1,r="marker"===s&&u===e.cid,i="marker"===s&&null!==u&&!r
return f.default.createElement(S.CommentThread,{key:e.cid,commentThreadCid:e.cid,commentMarkerIndex:a,isScrollFocus:r,isBlur:i,commentList:n,permission:o.commentOperations.getPermission(e.user_id),commentOperations:o.commentOperations})})),!d&&f.default.createElement("div",{className:"comment-thread-empty"},f.default.createElement("img",{src:_}),f.default.createElement("h3",null,k.preview.comment.add_comment),f.default.createElement("span",null,a.permissionDenyMessage||(
a.userAuthStatus===w.USER_AUTH_STATUS_NOT_SIGN_IN?k.preview.comment.thread_none_tip_signin:k.preview.comment.thread_none_tip))),a.isProjectAllowComment?this.renderContentReply():d?f.default.createElement("div",{className:"reply-footer"},f.default.createElement("span",null,k.renew_prompt.comment_deny_permission)):null,f.default.createElement(S.CommentHeaderGlobalStyle,null))}}]),t}(f.PureComponent)
t.CommentLayer=C,(0,d.default)(C,"propTypes",{isLoaded:p.default.bool,permissionPack:p.default.object,getUserProfile:p.default.func,screenName:p.default.string,commentThreadList:p.default.array,commentListMap:p.default.object,focusCommentThreadCid:p.default.string,focusSource:p.default.string,tempCommentThreadMarker:p.default.object,dispatch:p.default.func})
var x=h.default.div.withConfig({displayName:"CommentLayer__CommentPanelDiv",componentId:"wnjiq4-0"})([
"position:relative;display:flex;flex-flow:column;width:260px;height:100%;font-size:12px;background-color:#fff;box-shadow:0 -2px 30px rgba(39,54,78,0.11);z-index:1;& > .comment-title{display:flex;align-items:center;height:50px;margin:0 20px;border-bottom:1px solid #d9d9d9;}& > .comment-thread{flex:1;overflow-y:auto;padding:0 20px;}& > .comment-thread-empty{flex:1;display:flex;flex-flow:column;align-items:center;justify-content:center;& > img{width:90px;margin:0 10px;}& > h3{padding:10px;}& > span{padding:0 10px;text-align:center;}}& > .reply-footer{display:flex;align-items:flex-end;background:#fff;border-top:1px solid #eaebed;padding:10px 14px;box-shadow:0 -2px 10px rgba(26,58,109,0.12);& > div{margin:0 8px -4px 0;width:174px;max-height:120px;> label{"
,";& > textarea{padding:3px 8px;min-height:28px;}}}& > button{flex:1;height:28px;font-size:12px;}}"],(0,m.placeholder)({color:"#a9afb8"})),T=function(){window.location.href="/signin?next=".concat(window.location.pathname)},_="/images/preview/no-comment@2x.png"},"3xoc":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.getDarkerButton=void 0
var r=a(n("q1tI")),i=n("6XO9"),o={backgroundColor:"#5b6b73"},l={opacity:.6}
t.getDarkerButton=function(e,t,n){return r.default.createElement(i.Button,{type:"primary",style:n?l:o,onClick:t,disabled:n},e)}},"43RC":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=r(n("TSYQ")),m=r(n("i6OX")),v=n("5hhZ"),g=function(e){function i(){var e,n;(0,o.default)(this,i)
for(var t=arguments.length,a=new Array(t),r=0;r<t;r++)a[r]=arguments[r]
return n=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(n),"handleClick",function(){var e=n.props,t=e.isMinimized;(0,e.onClick)(!t)}),n}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props,t=e.placement,n=e.isMinimized,a="left"===t?"angle-right":"angle-left"
return p.default.createElement(v.StyledToggleButton,{className:(0,h.default)(t,{"is-minimized":n}),onClick:this.handleClick},p.default.createElement(m.default,{type:"fa",name:a,className:"toggle-icon"}))}}]),i}(p.PureComponent)
t.default=g,(0,f.default)(g,"propTypes",{placement:i.default.oneOf(["left","right"]),isMinimized:i.default.bool,onClick:i.default.func})},"4QcC":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),i=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=a(n("q1tI")),p=r(n("DKAG")),h=r(n("17x9")),m=n("i6OX"),v=r(n("Lyer")),g=r(n("EDI8")),y=r(n("UbMB")).default.bind(g.default),b=MB.config.SCALES,S=function(e){function t(){var i
return(0,o.default)(this,t),i=(0,l.default)(this,(0,s.default)(t).call(this)),(0,d.default)((0,c.default)(i),"handleZoomIn",function(){var e=i.props,t=e.scale,n=e.dispatch,a=e.fromFullScreen
MB.event("preview","工具栏 :点击缩放"),a&&MB.event("preview","工具栏 :全屏模式缩放")
var r=b.findIndex(function(e){return t<e})
n({type:"entry:preview:set:scale",payload:{scale:b[r]||b[b.length-1]}})}),(0,d.default)((0,c.default)(i),"handleZoomOut",function(){var e=i.props,t=e.scale,n=e.dispatch,a=e.fromFullScreen
MB.event("preview","工具栏 :点击缩放"),a&&MB.event("preview","工具栏 :全屏模式缩放")
var r=b.findIndex(function(e){return t<=e})
n({type:"entry:preview:set:scale",payload:{scale:b[r-1]||b[0]}})}),(0,d.default)((0,c.default)(i),"handleResetScale",function(){(0,i.props.dispatch)({type:"entry:preview:set:scale",payload:{scale:100}})}),(0,d.default)((0,c.default)(i),"handleKeyDown",function(e){w(e,i.handleZoomIn,i.handleZoomOut,i.handleResetScale)}),i.state={isGuideShow:!1},i}return(0,u.default)(t,e),(0,i.default)(t,[{key:"componentDidMount",value:function(){var e=this
this.props.fromFullScreen||(this.openGuideTimer=setTimeout(function(){e.setState({isGuideShow:!0})},600))}},{key:"componentWillUnmout",value:function(){clearTimeout(this.openGuideTimer)}},{key:"render",value:function(){var e=this.props.scale,t=this.state.isGuideShow,n=e<400,a=20<e
return f.default.createElement(v.default,{id:"preview-zoom",localeKey:"zoom",X:"left",isOpen:t,gotItBtn:!0,noCloseBtn:!0},f.default.createElement("div",{className:y("zoom-count","preview-zoom-btn")},f.default.createElement("a",{id:"zoomout",disabled:!a,title:I18N.zoomout,onClick:this.handleZoomOut,className:"scale-icon"},f.default.createElement(m.SVGIcon,{name:"design/scale_reduce"})),f.default.createElement("span",null,"".concat(Math.round(e),"%")),f.default.createElement("a",{id:"zoomin",disabled:!n,
title:I18N.zoomin,onClick:this.handleZoomIn,className:"scale-icon"},f.default.createElement(m.SVGIcon,{name:"design/scale_enlarge"})),f.default.createElement(p.default,{target:document,onKeyDown:this.handleKeyDown})))}}]),t}(f.PureComponent)
t.default=S,(0,d.default)(S,"propTypes",{scale:h.default.number,fromFullScreen:h.default.bool,dispatch:h.default.func}),(0,d.default)(S,"defaultProps",{fromFullScreen:!1})
var w=function(e,t,n,a){(e.ctrlKey||e.metaKey)&&(187==e.keyCode&&(e.preventDefault(),t()),189==e.keyCode&&(e.preventDefault(),n()),48==e.keyCode&&(e.preventDefault(),a()))}},"4WDG":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var R=r(n("J4zp")),i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),L=a(n("q1tI")),j=r(n("DKAG")),A=r(n("foKU")),B=r(n("tBsX")),D=n("oose"),O=r(n("dYO+")),F=r(n("DdUa")),q=r(n("kJQk")),W=r(n("9ZUU")),U=r(n("TSYQ"))
n("fSKh")
var p=function(e){function t(){var a
return(0,i.default)(this,t),a=(0,l.default)(this,(0,s.default)(t).call(this)),(0,d.default)((0,c.default)(a),"handleKeyDown",function(e){var t=a.props.dispatch,n=e.target.matches("input")||e.target.matches("textarea")
32===e.keyCode&&!n&&(e.preventDefault(),t({type:"preview:set:key:flags",payload:{isSpaceDown:!0}}))}),(0,d.default)((0,c.default)(a),"handleKeyUp",function(e){a.props.dispatch({type:"preview:reset:key:flags"})}),(0,d.default)((0,c.default)(a),"handleMouseDown",function(e){var t=a.props.isSpaceDown;(1===e.button||t)&&a.initDraggingCanvas(e)}),(0,d.default)((0,c.default)(a),"handleScaleChange",function(e){a.props.dispatch({type:"entry:preview:set:scale",payload:{scale:e}})}),(0,d.default)((0,c.default)(a),
"handleOffsetChange",function(e,t){a.props.dispatch({type:"entry:preview:set:canvas:offset",payload:{offset:{x:e,y:t}}})}),a.state={isDraggingCanvas:!1},a}return(0,u.default)(t,e),(0,o.default)(t,[{key:"initDraggingCanvas",value:function(e){var n=this,a=e.clientX,r=e.clientY,t=this.props.canvasOffset,i=t.x,o=t.y
this.setState({isDraggingCanvas:!0})
var l=function(e){var t={x:i+(e.clientX-a),y:o+(e.clientY-r)}
n.props.dispatch({type:"entry:preview:set:canvas:offset",payload:{offset:t}})}
document.addEventListener("mousemove",l),document.addEventListener("mouseup",function e(t){n.setState({isDraggingCanvas:!1}),document.removeEventListener("mousemove",l),document.removeEventListener("mouseup",e)})}},{key:"render",value:function(){var e=this.props,t=e.scale,n=e.canvasOffset,a=e.project,r=e.screen,i=e.isSpaceDown,o=e.isStickyShow,l=e.isScrollable,s=e.shellType,c=e.isLayerActive,u=e.isCommentActive,d=e.isColorPickerActive,f=e.isFullScreenMode,p=e.isLayerPreview,h=this.state.isDraggingCanvas,
m=n.x,v=n.y,g="landscape"===r.orientation,y=c||u,b=y||!l?"none":s,S=a.width,w=a.height,E=g?[w,S]:[S,w],k=(0,R.default)(E,2),C=k[0],x=k[1],T={width:C,height:x,minWidth:C,minHeight:x,transform:"matrix(1, 0, 0, 1, ".concat(m,", ").concat(v,")")},_={transform:"scale(".concat(t/100,")")},M={width:"".concat(t,"%"),height:"".concat(t,"%")},P={width:r.width*t/100,height:r.height*t/100},I=(0,U.default)({"wait-drag":i||h,"is-immersive":y,"is-layer-active":c,"is-screen-expanded":y||!l}),N=(0,U.default)("ui-layers",{
"is-shadow":!("default"===b&&p),"is-active":c})
return L.default.createElement(A.default,{x:m,y:v,scale:t,id:"simulator-container",className:I,isDisabled:h,onMouseDown:this.handleMouseDown,onScaleChange:this.handleScaleChange,onOffsetChange:this.handleOffsetChange},function(e,t,n){return L.default.createElement("div",{key:"1",className:(0,U.default)("screen-viewport",{"is-fullscreen":f,"is-geely":"car_play"===a.model}),style:T},L.default.createElement("div",{className:"zoom-area",style:_},L.default.createElement(F.default,null),
!y&&L.default.createElement(O.default,{project:a,shellType:b,isLandscape:g}),o&&L.default.createElement(W.default,null)),L.default.createElement("div",{className:"no-zoom-area-wrapper",style:M},L.default.createElement("div",{className:"no-zoom-area",style:p&&l?{}:P},L.default.createElement("div",{id:"ui-layers",className:N},d&&L.default.createElement(q.default,null),c&&!d&&L.default.createElement(B.default,null)),L.default.createElement("div",{id:"ui-comment-marker-panel"},L.default.createElement(
D.CommentMarkerPanelContainer,{isActive:u,scale:n/100})))))},L.default.createElement(j.default,{target:document,onKeyDown:this.handleKeyDown,onKeyUp:this.handleKeyUp}))}}]),t}(L.PureComponent);(t.default=p).propTypes={scale:f.default.number,canvasOffset:f.default.object,screen:f.default.object,project:f.default.object,shellType:f.default.string,isStickyShow:f.default.bool,isScrollable:f.default.bool,isLayerPreview:f.default.bool,isSpaceDown:f.default.bool,isLayerActive:f.default.bool,
isCommentActive:f.default.bool,isColorPickerActive:f.default.bool,dispatch:f.default.func,isFullScreenMode:f.default.bool}},"4YeV":function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("WVP6"),r=n("Ehhz").MODEL_OPERATION_MAP.ProjectAlike,i=(0,a.createStateStore)([]),o=i.getState,l=i.setState,s=i.wrapEntry,c=function(i,o){return s(function(e,t,n){var a=t.dispatch,r=n&&n.payload
a({type:"reducer:projects:update",payload:i(e,r,o)})})},u={entryMap:{"projects:refresh":c(r.refreshStateList,!1),"projects:add":c(r.addState,!1),"projects:add-local":c(r.addState,!0),"projects:update":c(r.updateState,!1),"projects:update-local":c(r.updateState,!0),"projects:delete":c(r.deleteState,!1),"projects:delete-local":c(r.deleteState,!0)},getState:o,setState:l}
t.default=u},"4daP":function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.playSettingEntry=void 0
var o=n("upRB"),l=n("7Qib"),s="preview-is-scrollable",c="preview-is-stickyshow",u="preview-is-highlight",d="preview-shell-type",a={"entry:init:preview-setting":function(e){var t=e.getState,n=e.dispatch,a=t(),r=(0,o.getCurrentProject)(a),i=(0,l.localStorageGetItem)(d)?(0,l.localStorageGetItem)(d):r.shell_type
n({type:"reducer:preview-toolbar:update",payload:{isScrollable:"false"!==(0,l.localStorageGetItem)(s),isStickyShow:"false"!==(0,l.localStorageGetItem)(c),isHighlight:(0,l.localStorageGetItem)(u)?"false"!==(0,l.localStorageGetItem)(u):r.highlight,shellType:i}})},"entry:preview-setting:update:is-highlight":function(e,t){var n=e.dispatch,a=t.payload.isHighlight;(0,l.localStorageSetItem)(u,a),n({type:"reducer:preview-toolbar:update",payload:{isHighlight:a}})},"entry:preview-setting:update:shell-type":function(e
,t){var n=e.dispatch,a=t.payload.shellType;(0,l.localStorageSetItem)("".concat(d,"-").concat(MB.currentProject.cid),a),n({type:"reducer:preview-toolbar:update",payload:{shellType:a}}),setTimeout(function(){MB.runner.reload()})},"entry:preview-setting:update:is-scrollable":function(e,t){var n=e.dispatch,a=t.payload.isScrollable;(0,l.localStorageSetItem)(s,a),n({type:"reducer:preview-toolbar:update",payload:{isScrollable:a}}),setTimeout(function(){MB.runner.reload()})},
"entry:preview-setting:update:is-sticky-show":function(e,t){var n=e.dispatch,a=t.payload.isStickyShow;(0,l.localStorageSetItem)(c,a),n({type:"reducer:preview-toolbar:update",payload:{isStickyShow:a}})}}
t.playSettingEntry=a},"4dyd":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=r(n("UJpD")),m=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"handleResize",function(){var e=t.elem.getBoundingClientRect()
t.props.onResize(e)}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"componentDidMount",value:function(){this.elem.contentWindow.addEventListener("resize",this.handleResize)}},{key:"componentWillUnmount",value:function(){var e=this.elem.contentWindow
e&&e.removeEventListener("resize",this.handleResize)}},{key:"render",value:function(){var t=this
return p.default.createElement("iframe",{ref:function(e){return t.elem=e},className:h.default.detector})}}]),i}(p.PureComponent);(t.default=m).propTypes={onResize:i.default.func.isRequired}},"4sCl":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),m=a(n("q1tI")),v=r(n("TSYQ")),g=r(n("SFPg")),p=n("/5+U"),y=n("veUc")
n("oKLx")
var h=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"state",{ifHideLayer:!1}),(0,f.default)((0,u.default)(t),"onMouseLeave",function(){"number"==typeof t.props.activeLayerID?t.props.enterLayer("artboard-base"):t.props.enterLayer(t.props.currentScreen.cid)}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"componentWillReceiveProps",value:function(e){var t=e.currentScreen,n=e.activeLayerID,a=this.props,r=a.currentScreen,i=a.enterLayer
t!=r&&i(-1),-1!==n&&n?this.setState({ifHideLayer:!1}):this.setState({ifHideLayer:!0})}},{key:"render",value:function(){var e=this.props,t=e.isShowLayerList,n=e.layers,a=e.currentScreen,r=e.unit,i=e.ratio,o=e.activeLayerID,l=e.enteredLayerID,s=e.enterLayer,c=e.requestSelectLayer,u=e.handleShowlayerInfo,d=this.state.ifHideLayer,f=(0,y.transformLayersFormat)(n),p=b(r,i,s,o,l,c,u),h={top:0,left:0,width:a.width,height:a.height}
return m.default.createElement("div",{className:(0,v.default)("LayerList",{hiddenLayer:d&&t}),onMouseLeave:this.onMouseLeave},f.map(function(e){return m.default.createElement(g.default,{key:e.id,layer:e,parentRect:h,treeProps:p})}))}}]),i}(m.Component)
t.default=h,(0,f.default)(h,"propTypes",{isSpaceDown:i.default.bool,layers:i.default.array,requestSelectLayer:i.default.func,resetLayer:i.default.func,artboard:i.default.object,enterLayer:i.default.func,handleShowlayerInfo:i.default.func,currentScreen:i.default.object,activeLayerID:i.default.oneOfType([i.default.number,i.default.string]),enteredLayerID:i.default.oneOfType([i.default.number,i.default.string]),isShowLayerList:i.default.bool,unit:i.default.string,ratio:i.default.number,dispatch:i.default.func}
)
var b=(0,p.immutableTransformCache)(function(e,t,n,a,r,i,o){return{unit:e,ratio:t,enterLayer:n,activeLayerID:a,enteredLayerID:r,requestSelectLayer:i,handleShowlayerInfo:o}})},"4vJh":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:i,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"reducer:preview-panel:search":return(0,r.default)({},e,a)
case"reducer:preview-panel:reset":return i
default:return e}}
var r=a(n("MVZn")),i={screenSearch:""}},"4x8W":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:i,t=1<arguments.length?arguments[1]:void 0
switch(t.type){case"event-sign-up:close:modal":return(0,r.default)({open:!1},e)
case"event-sign-up:set:event":return t.payload
default:return e}}
var r=a(n("MVZn")),i={open:!1,event:{}}},"5Mi5":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=a(n("a1gu")),l=a(n("Nsbk")),s=a(n("7W2i")),c=a(n("lSNA")),u=a(n("17x9")),d=n("q1tI"),f=n("2EV6"),p=window.key,h="preview",m=function(e){function t(){return(0,r.default)(this,t),(0,o.default)(this,(0,l.default)(t).apply(this,arguments))}return(0,s.default)(t,e),(0,i.default)(t,[{key:"componentDidMount",value:function(){var e=this.props.dispatch
p.setScope(h),p("command+enter, ctrl+enter",h,function(){e({type:"entry:enter:full-screen-mode"})}),p("command+p, ctrl+p",h,function(){return!1}),p("esc",h,function(){if("project"===(0,f.getProjectType)(MB.currentProject))return e({type:"entry:preview:escape:key"}),!1})}},{key:"componentWillUnmount",value:function(){p.deleteScope(h),p.setScope("design")}},{key:"render",value:function(){return null}}]),t}(d.PureComponent)
t.default=m,(0,c.default)(m,"propTypes",{dispatch:u.default.func})},"5hhZ":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledToggleButton=void 0
var r=a(n("vOnD")).default.div.withConfig({displayName:"styles__StyledToggleButton",componentId:"sc-1g67xqq-0"})([
"position:absolute;z-index:1;cursor:pointer;display:flex;align-items:center;justify-content:center;top:50%;margin-top:-46px;width:14px;height:93px;background:#fff;&.left{right:100%;border-top-left-radius:35px;border-bottom-left-radius:35px;}&.right{left:100%;border-top-right-radius:35px;border-bottom-right-radius:35px;}.toggle-icon{width:10px;font-size:18px;color:#8d9ea7;text-align:center;transform:rotate(0);transition:transform 0.5s ease;}&.is-minimized{.toggle-icon{transform:rotate(180deg);}}"])
t.StyledToggleButton=r},6:function(e,t,n){n("j36g"),n("55Il"),e.exports=n("Z3xQ")},"6PGs":function(e,t,n){e.exports={"screen-info":"_1AJNH2RNIDeT2zJnKkRP2E"}},"6UMJ":function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.keyEntry=void 0
var o=n("upRB"),a={"entry:preview:escape:key":function(e){var t=e.getState,n=e.dispatch,a=t(),r=(0,o.getIsFullScreenMode)(a),i=(0,o.getisShowColorPicker)(a)
r?(n({type:"reducer:preview-toolbar:fullscreen",payload:{isFullScreenMode:!1}}),n({type:"entry:init:preview:scale"}),n({type:"preview:set:canvas:offset",payload:{offset:{x:0,y:0}}})):MB.designer&&!i&&MB.designer.backDesign()}}
t.keyEntry=a},"6Y1W":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("x3zb")),m=r(n("ibfc")),v=function(e){function t(e){var r
return(0,i.default)(this,t),r=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(r),"handleHomeScreenLoad",function(e){console.log("HomeScreenLoad",e),MB.runner.doneTransition(e)}),(0,d.default)((0,c.default)(r),"handleTransitionEnd",function(e){var t=r.props.transition,n=t.name,a=t.callback;/(menu|drawer)-reverse/.test(n)&&(console.log("menu - closed"),MB.runner.currentMenu=MB.runner.currentScreen=null),console.log("transition - end"),MB.runner.doneTransition(e),a&&a()}),
r.state={prevScreenCid:"",currentScreenCid:e.activeCid},r}return(0,u.default)(t,e),(0,o.default)(t,[{key:"componentDidMount",value:function(){console.log("mb runner did mount",{props:this.props.activeCid,state:this.state.currentScreenCid})}},{key:"componentWillUnmount",value:function(){console.log("mb runner will unmount")}},{key:"render",value:function(){var e=this.props,t=e.screenInfoMap,n=e.transition,o=e.widgetQueryMap,a=this.state,l=a.prevScreenCid,s=a.currentScreenCid
return s?p.default.createElement(h.default,{activeCid:s,transition:n,onHomeScreenLoad:this.handleHomeScreenLoad,onTransitionEnd:this.handleTransitionEnd},function(r,i){return Object.values(t).map(function(e){var t=e.cid===l,n=e.cid===s,a=t?r:n?i:null
return p.default.createElement(m.default,{key:e.cid,isShow:t||n,screen:e,style:a,isActive:s===e.cid,widgetQueryMap:o})})}):null}}]),t}(p.PureComponent)
t.default=v,(0,d.default)(v,"propTypes",{widgetQueryMap:f.default.object,screenInfoMap:f.default.object,activeCid:f.default.string,transition:f.default.object}),(0,d.default)(v,"getDerivedStateFromProps",function(e,t){return e.activeCid!==t.currentScreenCid?{prevScreenCid:t.currentScreenCid,currentScreenCid:e.activeCid}:null})},"6ZRU":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("MVZn")),i=n("/MKj"),o=a(n("/cyv")),l=a(n("HfeQ")),s={Alert:(0,i.connect)(function(e){return(0,r.default)({},e.container.alert)})(l.default)},c={reducers:o.default,containers:s}
t.default=c},"6gQ3":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=a(n("rESR")),o=n("/5+U"),l=(0,r.connect)(function(e){var t=e.model,n=t.user,a=t.current.projectCid,r=t.projects,i=t.screens,o=e.container,l=o.common.offset,s=o.previewSetting.toolbarActiveItem,c=!!n.id,u=Boolean(l.x||l.y),d=h(r,a),f=p.has(d.access_token)
return{isLoggedIn:c,isDisplaced:u,screensCount:i.reduce(function(e,t){return t.project_cid===a?e+1:e},0),project:d,isDemo:f,toolbarActiveItem:s}})(i.default)
t.default=l
var p=new Set(["demo","cS1AXKF5jtrJePbEKiYcdcHosQPdzrk","workout","sI3GY2tDz76RrZ4MGFiIcZTZpAHyluC","UMQzYmknxWeHNvvVyeyJDuSkgyvi6Xw","9Py1L5RdC8ZPRSmnWEt4uuUUSDUAxkM"]),h=(0,o.immutableTransformCache)(function(e,t){return e.find(function(e){return e.cid===t})})},"6iHT":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.CommentHeaderGlobalStyle=t.ContentHeader=t.ContentMessage=t.commonContentFooter=void 0
var i=r(n("VkAN")),l=r(n("q1tI")),o=r(n("17x9")),s=a(n("vOnD")),c=n("6XO9"),u=r(n("zkrS")),d=r(n("i6OX")),f=n("wYtL"),p=n("FC/4"),h=n("3xoc")
function m(){var e=(0,i.default)(["\n  .comment-header-edit li:hover { color: #1e98ea; }\n  .comment-header-delete li:hover { color: #eb5648; }\n"])
return m=function(){return e},e}var v=u.default.I18N,g=u.default.L10N
t.commonContentFooter=function(e,t,n,a,r){return[l.default.createElement(y,{key:"footer"},g.parseTimeAgo(1e3*e.updated_at),a&&l.default.createElement(b,{onClick:t?r:a},l.default.createElement(d.default,{type:"dora",name:"reply"}),t?v.preview.comment.cancel_reply:v.preview.comment.comment_create)),t&&l.default.createElement(S,{key:"reply"},l.default.createElement(p.TextEditComponent,{textEditStore:t,placeholder:v.preview.comment.comment_placeholder,minHeight:60,autoHeight:!0,multiline:!0}),(0,
h.getDarkerButton)(v.preview.comment.comment_create,t.endEdit,!n))]}
var y=s.default.div.withConfig({displayName:"CommentLayerThreadContent__ContentFooterDiv",componentId:"sc-1lkzl71-0"})(["display:flex;align-items:center;justify-content:space-between;padding:0 10px 10px;line-height:20px;color:#8d9ea7;opacity:0.75;"]),b=s.default.div.withConfig({displayName:"CommentLayerThreadContent__ReplyToggleDiv",componentId:"sc-1lkzl71-1"})(["cursor:pointer;&:hover,&:active{color:#525e71;}> span{margin-right:6px;opacity:0.5;}"]),S=s.default.div.withConfig({
displayName:"CommentLayerThreadContent__ReplyDropdownDiv",componentId:"sc-1lkzl71-2"})(["padding:10px 0;background:#fff;> button{width:100%;height:24px;font-size:12px;}"]),w=function(e){var t=e.sub,n=e.comment,a=e.textEditStore,r=e.cancelEdit
return l.default.createElement(E,{className:t?"sub":""},a?l.default.createElement(C,null,l.default.createElement(p.TextEditComponent,{textEditStore:a,placeholder:v.preview.comment.comment_placeholder,minHeight:60,autoHeight:!0,multiline:!0}),l.default.createElement(x,null,l.default.createElement(c.Button,{onClick:r},v.preview.comment.cancelEdit),l.default.createElement(c.Button,{type:"primary",onClick:a.endEdit},v.preview.comment.updateEdit))):l.default.createElement(k,null,n.message))};(t.ContentMessage=w
).propTypes={sub:o.default.bool,comment:o.default.object,textEditStore:o.default.object,cancelEdit:o.default.func}
var E=s.default.div.withConfig({displayName:"CommentLayerThreadContent__ContentMessageDiv",componentId:"sc-1lkzl71-3"})(["display:flex;flex-flow:column;width:100%;height:auto;color:#5b6b73;white-space:nowrap;text-overflow:ellipsis;span{padding:10px;}&.sub span{padding:0 10px 10px;}"]),k=s.default.span.withConfig({displayName:"CommentLayerThreadContent__EditableSpanSpan",componentId:"sc-1lkzl71-4"})(["user-select:text;word-break:break-all;white-space:pre-line;text-overflow:ellipsis;"]),
C=s.default.div.withConfig({displayName:"CommentLayerThreadContent__EditableSpanDiv",componentId:"sc-1lkzl71-5"})(["background:#fff;> textarea{margin-bottom:5px;padding:10px;border:1px solid #d3dce6;}"]),x=s.default.div.withConfig({displayName:"CommentLayerThreadContent__ButtonPanelDiv",componentId:"sc-1lkzl71-6"})(["display:flex;justify-content:flex-end;width:100%;> button{width:60px;height:24px;font-size:12px;margin-left:10px;}"]),T=function(e){var t=e.sub,n=e.avatar,a=e.name,r=e.markIndex,i=e.startEdit,
o=e.doDelete
return l.default.createElement(_,{className:t?"sub":""},l.default.createElement(I,null,l.default.createElement("img",{src:n,width:24,height:24}),l.default.createElement("div",null,r&&l.default.createElement("span",{className:"index"},"#".concat(r)),l.default.createElement("span",{className:"name"},a))),l.default.createElement(M,null,i&&l.default.createElement(N,{onSelect:i,menuClassName:"comment-header-edit",iconName:"cog",text:v.preview.comment.modify_edit}),o&&l.default.createElement(N,{onSelect:o,
menuClassName:"comment-header-delete",iconName:"trash",text:v.preview.comment.modify_delete})))};(t.ContentHeader=T).propTypes={avatar:o.default.string,name:o.default.string,markIndex:o.default.number,startEdit:o.default.func,doDelete:o.default.func,sub:o.default.bool}
var _=s.default.div.withConfig({displayName:"CommentLayerThreadContent__ContentHeaderDiv",componentId:"sc-1lkzl71-7"})(["display:flex;justify-content:space-between;padding-bottom:10px;width:100%;&.sub{padding:10px;}"]),M=s.default.div.withConfig({displayName:"CommentLayerThreadContent__ContentHeaderEditDiv",componentId:"sc-1lkzl71-8"})(["display:flex;align-items:center;.icon{color:#c8cdd0;margin-left:5px;&:hover,&:active{color:#8d9ea7;}}"]),P=(0,s.createGlobalStyle)(m())
t.CommentHeaderGlobalStyle=P
var I=s.default.div.withConfig({displayName:"CommentLayerThreadContent__UserInfoDiv",componentId:"sc-1lkzl71-9"})(["display:flex;height:24px;> img{margin-right:10px;border-radius:100%;}> div{display:flex;flex-flow:column;justify-content:center;max-height:24px;font-weight:bold;line-height:12px;.index{vertical-align:middle;color:#f55d54;}.name{max-width:140px;color:#5b6b73;overflow:hidden;white-space:nowrap;text-overflow:ellipsis;}}"]),N=function(e){var t=e.onSelect,n=e.text,a=e.iconName,r=e.menuClassName
return l.default.createElement(f.Tooltip,{content:{hover:n},duration:1e3,position:"left"},l.default.createElement(c.Dropdown,{opener:l.default.createElement(d.default,{type:"dora",name:a}),onSelect:t,menuClassName:r,menuList:[n],menuX:"right",arrowed:!0}))}
N.propTypes={onSelect:o.default.func.isRequired,text:o.default.string.isRequired,iconName:o.default.string.isRequired,menuClassName:o.default.string.isRequired}},"7Rdd":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=a(n("q1tI")),r=a(n("17x9")),l=n("1qiG"),i=function(e){var t=e.refRect,n=e.screen,a=e.style,r=a.dashed,i=a.colorForLines
return o.default.createElement("div",{style:{position:"absolute",pointerEvents:"none",width:(0,l.toPercentage)(t.width/n.width),height:(0,l.toPercentage)(t.height/n.height),left:(0,l.toPercentage)(t.left/n.width),top:(0,l.toPercentage)(t.top/n.height),border:"1px ".concat(r?"dashed":"solid"," ").concat(i)}})}
i.propTypes={refRect:r.default.object,screen:r.default.object,style:r.default.object}
var s=i
t.default=s},"7bR1":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.setVisibilityScreen=v,t.default=C
var c=a(n("o0o1")),y=a(n("MVZn")),r=a(n("J2m7")),u=n("oZtI"),d=n("upRB"),f=n("JfQ8"),s=n("Kkl0"),b=n("jvRN"),p=n("7q5O"),h=c.default.mark(v),i=c.default.mark(g),m=c.default.mark(w),o=c.default.mark(E),l=c.default.mark(C),S=[]
function v(e){var t,n,a,r,i,v,g,o,l,s
return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,u.select)()
case 2:if(t=e.sent,n=t.container.layers,a=n.resourceByScreen,r=n.visibilityScreenID,i=t.model.widgets,v=(0,d.getCurrentScreen)(t),a[r]&&!a[r].error){e.next=26
break}if(S.includes(r)){e.next=26
break}return S.push(r),e.prev=8,e.next=11,(0,u.call)(p.getLayerData,v,i)
case 11:return g=e.sent,o=(0,b.getMockingBotWidgets)(t),l=[{type:"screen",id:v.cid,name:v.name,top:0,left:0,width:v.width,height:v.height,src_left:0,src_top:0,src_width:g.artboard.width,src_height:g.artboard.height,bg_colors:[{value:(0,b.checkColor)(v.bgcolor)}]}].concat(g.layers).concat(o).reduce(function(e,t){var n=t.id,a=t.top,r=t.left,i=t.width,o=t.height
if("group"===t.name)return e.push(t),e
var l=(0,b.isSketchLayer)(n)?g.artboard.widgetWidth/g.artboard.width:1,s=a*l,c=r*l,u=i*l,d=o*l,f=Math.min(Math.max(c,0),v.width),p=Math.min(Math.max(c+u,0),v.width),h=Math.min(Math.max(s,0),v.height),m=Math.min(Math.max(s+d,0),v.height)
return p-f!=0&&m-h!=0&&e.push((0,y.default)({},t,{left:f,top:h,width:p-f,height:m-h,src_top:Number(parseFloat(Math.max(a,0)).toFixed(2)),src_left:Number(parseFloat(Math.max(r,0)).toFixed(2)),src_width:Number(parseFloat(Math.min(r+i,g.artboard.width)-Math.max(r,0)).toFixed(2)),src_height:Number(parseFloat(Math.min(a+o,g.artboard.height)-Math.max(a,0)).toFixed(2))})),e},[]),s=(0,y.default)({},g,{layers:l}),S.splice(S.indexOf(r),1),e.next=18,(0,u.put)((0,f.receiveResourceSuccess)(r,s))
case 18:e.next=26
break
case 20:return e.prev=20,e.t0=e.catch(8),console.log(e.t0.stack),S.splice(S.indexOf(r),1),e.next=26,(0,u.put)((0,f.receiveResourceError)(r,e.t0.message))
case 26:case"end":return e.stop()}},h,null,[[8,20]])}function g(){return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,u.takeEvery)(f.SET_VISIBILITY_SCREEN,v)
case 2:case"end":return e.stop()}},i)}function w(t){var n,a,r,i,o,l
return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.payload.layerID,e.next=3,(0,u.select)()
case 3:return a=e.sent,r=a.container.layers,i=r.resourceByScreen,o=r.visibilityScreenID,l=k(i[o].layers,n),e.next=9,(0,u.put)((0,s.selectLayer)(l))
case 9:return e.next=11,(0,u.put)((0,s.activateLayer)(l))
case 11:case"end":return e.stop()}},m)}function E(){return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,u.takeEvery)(s.REQUEST_SELECT_LAYER,w)
case 2:case"end":return e.stop()}},o)}var k=function(e,t){var n=(0,r.default)(e,{id:t})
if(!n||!n.parent||n.image_set_zip)return t
for(;n;){var a=(0,r.default)(e,{id:n.parent})
if(!a||!a.image_set_zip||!a.parent)return t
if(a.image_set_zip)return n.parent
n=a.parent}}
function C(){return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,[g(),E()]
case 2:case"end":return e.stop()}},l)}},"7eYF":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var s=a(n("RIqP")),c=a(n("MVZn")),d=a(n("o0o1")),f=n("ANjH"),p=n("WVP6"),h=a(n("sINF")),m=a(n("7bO/")),r=n("/TnQ"),u=n("IV71"),v=n("mreW"),g=n("nU12"),y=(0,r.composeWithDevTools)({})
t.default=function(e){var t=e.viewMap,n=e.containerReducerMap,a=e.sagaMap,r=e.extendCallback,i=new u.WebpackInterface
if(t)for(var o in t)i.setView(o,t[o])
var l=function(e){var n,t=e.entryMap,a=e.reducerMap,r=e.sagaMap,i=(0,p.createReduxEntry)(),o=i.middleware;(0,i.setEntryMap)(t)
var l=[o]
r&&(n=(0,m.default)(),l.push(n))
var s=(0,f.createStore)((0,f.combineReducers)(a),y(f.applyMiddleware.apply(void 0,l.concat([h.default]))))
if(r){var c=function(t){n.run(d.default.mark(function e(){return d.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=3,r[t]()
case 3:e.next=0
break
case 5:case"end":return e.stop()}},e)}))}
for(var u in r)c(u)}return{store:s}}({initialState:{model:{},container:{}},entryMap:(0,c.default)({},g.entryMap,v.entryMap,{"entry:webpack-interface:view:call":function(e,t){var n=t.payload
setTimeout(function(){return i.callViewMethod.apply(i,[n.name,n.method].concat((0,s.default)(n.args||{})))},0)}}),reducerMap:{model:(0,f.combineReducers)(g.reducerMap),container:(0,f.combineReducers)(n)},sagaMap:a}).store
return i.setStore(l),r&&r(i),i}},"7q5O":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.getLayerData=void 0
var l=a(n("o0o1")),r=a(n("yXPU")),s=n("t3Un"),i=function(){var n=(0,r.default)(l.default.mark(function e(a,r){var i,o
return l.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(!(i=a.artboard_id&&r.find(function(e){return e.screen_cid===a.cid&&"image_view"===e.name&&e.image&&-1!==e.image.indexOf(String("/artboard_"))}))){e.next=13
break}if(!window.MBArtboards){e.next=6
break}n=a.cid,o=window.MBArtboards[n],e.next=9
break
case 6:return e.next=8,t=a.artboard_id,(0,s.requestJSON)("".concat("/api/v2/sketch","/artboards/").concat(t,".json"))
case 8:o=e.sent
case 9:u(o,i),c(o),e.next=14
break
case 13:o={artboard:{top:0,left:0,width:a.width,height:a.height},layers:[],document:{document_colors:[],text_styles:[],global_colors:[]}}
case 14:return e.abrupt("return",o)
case 15:case"end":return e.stop()}var t,n},e)}))
return function(e,t){return n.apply(this,arguments)}}()
t.getLayerData=i
var c=function(e){e.layers.some(function(e){return e.z})?e.layers.sort(function(e,t){return e.z-t.z}):e.layers.sort(function(e,t){return parseInt(t.width)*parseInt(t.height)-parseInt(e.width)*parseInt(e.height)})},u=function(e,t){Object.assign(e.artboard,{widgetZ:t.z,widgetTop:t.top,widgetLeft:t.left,widgetWidth:t.width,widgetHeight:t.height}),e.layers.push({id:"artboard-base",name:e.artboard.name,type:"screen",top:0,left:0,z:t.z,width:e.artboard.width,height:e.artboard.height,bg_colors:[{value:t.bg}],
timestamp:t.timestamp+1})}},"80la":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.reducer=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:i,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"reducer:slice:success":return(0,r.default)({},e,a,{loading:!1})
case"reducer:slice:fail":return(0,r.default)({},e,a,{error:!0})
default:return e}}
var r=a(n("MVZn")),i={slices:[],loading:!0,error:!1}},"81q6":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=r(n("i6OX")),m=n("iLpg"),v=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"setInputRef",function(e){return t.$input=e}),(0,f.default)((0,u.default)(t),"focus",function(){return t.$input.focus()}),(0,f.default)((0,u.default)(t),"handleChange",function(e){t.props.onChange(e.target.value)}),(0,f.default)((0,u.default)(t),"handleClear",function(){t.props.onChange("")}),(0,f.default)((0,u.default)(t),"handleMouseDown",function(e){e.preventDefault()}),(0,f.default)((0,
u.default)(t),"handleKeyDown",function(e){"Escape"===e.key&&t.props.onExit&&t.props.onExit()}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props,t=e.value,n=e.placeholder,a=e.className,r=e.inputStyle
return p.default.createElement(m.StyledSearchBar,{type:"search",className:a},p.default.createElement(h.default,{type:"dora",name:"scale",className:"search-icon"}),p.default.createElement("input",{ref:this.setInputRef,style:r,type:"text",value:t,placeholder:n,onChange:this.handleChange,onKeyDown:this.handleKeyDown}),0<t.length&&p.default.createElement(h.default,{type:"dora",name:"times_fc",className:"clear-icon",onMouseDown:this.handleMouseDown,onClick:this.handleClear}))}}]),i}(p.PureComponent)
t.default=v,(0,f.default)(v,"propTypes",{value:i.default.string,inputStyle:i.default.object,placeholder:i.default.string,className:i.default.string,onChange:i.default.func,onExit:i.default.func})},"8CMD":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("o0o1")),l=r(n("yXPU")),i=r(n("lwsE")),s=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("PJYZ")),f=r(n("7W2i")),p=r(n("lSNA")),h=r(n("17x9")),m=a(n("q1tI")),v=n("QQiC"),g=n("2M3O"),y=(0,v.createAsyncTaskQueue)().pushTask,b=function(e){function n(e){var t
return(0,i.default)(this,n),t=(0,c.default)(this,(0,u.default)(n).call(this,e)),(0,p.default)((0,d.default)(t),"setElementRef",function(e){return t.$elem=e}),t.isUnmounted=!1,t.retryTimer=null,t}return(0,f.default)(n,e),(0,s.default)(n,[{key:"componentDidMount",value:function(){this.props.isVisible&&this.generateSnapshotTask()}},{key:"componentDidUpdate",value:function(e,t){this.props.isVisible&&(clearTimeout(this.retryTimer),this.generateSnapshotTask())}},{key:"componentWillUnmount",value:function(){
this.isUnmounted=!0,clearTimeout(this.retryTimer)}},{key:"generateSnapshotTask",value:function(){var i=this,t=0<arguments.length&&void 0!==arguments[0]?arguments[0]:5
y((0,l.default)(o.default.mark(function e(){var t,n,a,r
return o.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(t=i.props,n=t.projectToken,a=t.screenCid,r=t.version,t.isVisible){e.next=3
break}return e.abrupt("return")
case 3:if(i.isUnmounted)return e.abrupt("return")
e.next=5
break
case 5:return e.next=7,(0,g.requestThumbnail)({imageElement:i.$elem,projectAccessToken:n,screenCid:a,version:r})
case 7:case"end":return e.stop()}},e)}))).catch(function(e){i.retryTimer=setTimeout(function(){i.generateSnapshotTask(2*t)},1e3*t)})}},{key:"render",value:function(){return m.default.createElement("img",{ref:this.setElementRef,src:"/images/preview/image-load.png"})}}]),n}(m.PureComponent)
t.default=b,(0,p.default)(b,"propTypes",{projectToken:h.default.string.isRequired,screenCid:h.default.string.isRequired,version:h.default.string,isVisible:h.default.bool.isRequired})},"8Fba":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var s=r(n("J4zp")),i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),c=r(n("Nsbk")),d=r(n("PJYZ")),u=r(n("7W2i")),f=r(n("lSNA")),h=a(n("q1tI")),m=r(n("DKAG")),p=r(n("17x9")),v=n("/5+U")
n("v8PR")
var g="hidden",y=function(e){function n(e){var u;(0,i.default)(this,n),u=(0,l.default)(this,(0,c.default)(n).call(this,e)),(0,f.default)((0,d.default)(u),"cancelColorPicker",function(e){u.imageCanvas.contains(e.target)||u.cancelPickerMode()}),(0,f.default)((0,d.default)(u),"cancelPickerMode",function(){return u.props.dispatch({type:"reducer:preview-toolbar:update",payload:{isShowColorPicker:!1}})}),(0,f.default)((0,d.default)(u),"renderImageCanvas",function(){var e=u.imageCanvas.getBoundingClientRect(),
t=e.width,n=e.height
u.lastCanvasRect={width:t,height:n},u.imageCanvas.width=t,u.imageCanvas.height=n,u.imageCtx.drawImage(u.image,0,0,t,n)}),(0,f.default)((0,d.default)(u),"calculateCenterPoint",function(e){var t=u.image.getBoundingClientRect(),n=t.left,a=t.top
u.centerPoint={centerX:Math.floor(e.clientX-n),centerY:Math.floor(e.clientY-a)}}),(0,f.default)((0,d.default)(u),"handleMove",function(e){u.image.complete&&u.state.visibility===g&&u.setState({visibility:"visible"}),u.calculateCenterPoint(e)
var t=u.props,n=t.glassHeight,a=t.glassWidth,r=t.scale,i=u.centerPoint,o=i.centerX,l=i.centerY,s=Math.floor(o-a/2),c=Math.floor(l-n/2)
u.setState({glassLeft:s,glassTop:c}),l<0&&u.clearGlassRect(),u.glassCtx.clearRect(0,0,a,n),r<1&&console.warn("Can't make the galss scale less than 1, It will make bed invision"),C(u.glassCtx,!1),u.glassCtx.drawImage(u.imageCanvas,Math.floor(o-a/2/u.finallyScale),Math.floor(l-n/2/u.finallyScale),Math.floor(a/u.finallyScale),Math.floor(n/u.finallyScale),-5,-5,a,n),k(u.glassCtx,"lightgray",10,10),x(u.glassCtx),T(u.glassCtx,"black",Math.floor((a-10)/2),Math.floor((n-10)/2),10,10),u.getColor()}),(0,f.default)((0
,d.default)(u),"getColor",function(){var e=u.centerPoint,t=e.centerX,n=e.centerY,a=u.imageCtx.getImageData(t,n,1,1).data,r=b(a),i=r.rgba,o=r.R,l=r.G,s=r.B
u.setState({color:i,R:o,G:l,B:s}),u.color=i}),(0,f.default)((0,d.default)(u),"handleClick",function(){u.getColor()
var e=u.color,t=(0,v.saveRecentColor)(e),n=t.history,a=t.focusColor
clearTimeout(u.timeoutToken),u.props.dispatch({type:"reducer:preview-toolbar:update",payload:{userPickColor:n,focusColor:a}}),u.timeoutToken=setTimeout(function(){u.props.dispatch({type:"reducer:preview-toolbar:update",payload:{userPickColor:n,focusColor:null}})},1e3)}),(0,f.default)((0,d.default)(u),"clearGlassRect",function(){var e=u.props,t=e.glassHeight,n=e.glassWidth
u.glassCtx.clearRect(0,0,n,t),u.setState({visibility:g})}),(0,f.default)((0,d.default)(u),"handleMouseLeave",function(){u.clearGlassRect()}),(0,f.default)((0,d.default)(u),"handleKeyDown",function(e){"escape"===e.key.toLowerCase()&&(u.clearGlassRect(),u.cancelPickerMode())}),(0,f.default)((0,d.default)(u),"handleLoad",function(){u.renderImageCanvas()}),(0,f.default)((0,d.default)(u),"handleError",function(){u.cancelPickerMode()})
var t=u.props.scale
return u.iamgeContainerRef=function(e){return u.image=e},u.getImageCanvasRef=function(e){return u.imageCanvas=e},u.glassCanvasRef=function(e){return u.glassCanvas=e},u.finallyScale=10*(t<1?1:t),u.state={visibility:g,glassLeft:0,glassTop:0,color:"#fff",R:0,G:0,B:0},u}return(0,u.default)(n,e),(0,o.default)(n,[{key:"componentDidMount",value:function(){this.imageCtx=this.imageCanvas.getContext("2d"),this.glassCtx=this.glassCanvas.getContext("2d")}},{key:"componentDidCatch",value:function(e){console.log(e),
this.cancelPickerMode()}},{key:"componentDidUpdate",value:function(){if(this.imageCanvas){var e=this.imageCanvas.getBoundingClientRect(),t=e.width,n=e.height,a=this.lastCanvasRect||{width:0,height:0},r=a.width,i=a.height
r==t&&i==n||(this.clearGlassRect(),this.renderImageCanvas())}else this.handleError()}},{key:"render",value:function(){var e=this.props,t=e.width,n=e.height,a=e.glassWidth,r=e.glassHeight,i=e.src,o=this.state,l=o.visibility,s=o.glassLeft,c=o.glassTop,u=o.color,d=o.R,f=o.G,p=o.B
return h.default.createElement("div",{className:"mb-picker-container"},h.default.createElement("img",{ref:this.iamgeContainerRef,className:"mb-picker-image",width:t,height:n,src:i,onLoad:this.handleLoad,onError:this.handleError}),h.default.createElement("canvas",{ref:this.getImageCanvasRef,onMouseMove:this.handleMove,onMouseLeave:this.handleMouseLeave,onClick:this.handleClick,style:{width:t,height:n,opacity:0}}),h.default.createElement("div",{className:"mb-glass",style:{width:a,height:r,visibility:l,left:s,
top:c}},h.default.createElement("div",{className:"shadow"}),h.default.createElement("canvas",{ref:this.glassCanvasRef,width:a,height:r,style:{width:a,height:r}}),h.default.createElement("div",{style:{top:r/2+15},className:"mb-glass-text"},h.default.createElement("div",{className:"mb-rgba-color"},"R:".concat(d," G:").concat(f," B:").concat(p," ").concat(String(w(u).hex).toUpperCase())))),h.default.createElement(m.default,{target:document,onKeyDown:this.handleKeyDown,onClick:this.cancelColorPicker}))}}]),n}(
h.PureComponent)
t.default=y,(0,f.default)(y,"propTypes",{src:p.default.string,width:p.default.oneOfType([p.default.string,p.default.number]),height:p.default.oneOfType([p.default.string,p.default.number]),glassHeight:p.default.number,glassWidth:p.default.number,scale:p.default.number,dispatch:p.default.func}),(0,f.default)(y,"defaultProps",{src:"/sec3.png",width:1300,height:769,glassWidth:200,glassHeight:200,scale:1,pickColor:function(e){return console.log(e)}})
var b=function(e){return e[3]=parseFloat(e[3]/255),{rgba:"rgba(".concat(e.join(", "),")"),R:e[0],G:e[1],B:e[2]}},S=/rgba?\((\d+),(\d+),(\d+),?(\d+)?/,w=function(e){var t=S.exec(e.replace(/ /g,"").toLowerCase())
if(!t||!t[3])return e
var n=(0,s.default)(t,5),a=n[1],r=n[2],i=n[3],o=n[4],l=void 0===o?"1":o
return{hex:"#".concat(E(a)).concat(E(r)).concat(E(i)),o:Number(l)}},E=function(e){var t=parseInt(e,10).toString(16)
return 1===t.length?"0".concat(t):t},k=function(e,t,n,a){e.strokeStyle=t,e.lineWidth=.5
for(var r=n+5.5;r<e.canvas.width-n;r+=n)e.beginPath(),e.moveTo(r,0),e.lineTo(r,e.canvas.height),e.stroke()
for(var i=a+5.5;i<e.canvas.height-n;i+=a)e.beginPath(),e.moveTo(0,i),e.lineTo(e.canvas.width,i),e.stroke()},C=function(e,t){e.mozImageSmoothingEnabled=t,e.webkitImageSmoothingEnabled=t,e.msImageSmoothingEnabled=t,e.imageSmoothingEnabled=t},x=function(e){e.beginPath(),e.strokeStyle="#8D9EA7",e.lineWidth=8,e.arc(100,100,96,0,2*Math.PI),e.stroke(),e.strokeStyle="#D4D7DC",e.lineWidth=5,e.arc(100,100,96,0,2*Math.PI),e.stroke()},T=function(e,t,n,a,r,i){e.beginPath(),n+=.5,a+=.5,e.strokeStyle=t,e.lineWidth=1,
e.moveTo(n,a),e.lineTo(n+r,a),e.lineTo(n+r,a+i),e.lineTo(n,a+i),e.lineTo(n,a),e.stroke(),e.beginPath(),e.lineWidth=1,e.strokeStyle="white",e.moveTo(n-1,a-1),e.lineTo(n+r+1,a-1),e.lineTo(n+r+1,a+1+i),e.lineTo(n-1,a+i+1),e.lineTo(n-1,a-1),e.stroke()}},"8jgF":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("MVZn")),l=r(n("lwsE")),i=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),h=r(n("17x9")),m=n("6XO9"),v=r(n("i6OX")),g=n("zAG7"),y=n("7Qib")
n("oSKl")
var b=function(e){function r(){var e,i;(0,l.default)(this,r)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return i=(0,s.default)(this,(e=(0,c.default)(r)).call.apply(e,[this].concat(n))),(0,f.default)((0,u.default)(i),"state",{formData:{name:"",email:"",pwd:""},submitErrMsg:"",submitted:!1}),(0,f.default)((0,u.default)(i),"handleFormDataChange",function(t){return function(e){return i.setState({formData:(0,o.default)({},i.state.formData,(0,f.default)({},t,e))})}}),(0,f.default)((0,u.default)(i),"handleEmailChange",function(e){return i.setState({formData:(0,o.default)({},i.state.formData,{email:e})})}),(0,
f.default)((0,u.default)(i),"resetSubmitErrMsg",function(){return i.setState({submitErrMsg:""})}),(0,f.default)((0,u.default)(i),"verifyEmail",function(e){return g.EMAIL_REG.test(e)}),(0,f.default)((0,u.default)(i),"handleSignUp",function(){var e=i.props.event,t=i.state.formData,n=t.name,a=t.email,r=t.pwd
if(i.resetSubmitErrMsg(),!i.verifyEmail(a))return i.setState({submitErrMsg:I18N.design.verify_email_address});(0,y.post)("/events/sign_up.json",{username:n,email:a,password:r,locale:"zh-CN",event:e.name}).then(function(){return(0,y.post)("/sessions.json",{email:a,password:r}).then(function(){return i.setState({submitted:!0})})},function(e){return i.setState({submitErrMsg:e.detail})})}),i}return(0,d.default)(r,e),(0,i.default)(r,[{key:"render",value:function(){var e=this.props,t=e.inMobile,n=e.isOpen,
a=e.event,r=this.state,i=r.formData,o=i.name,l=i.email,s=i.pwd,c=r.submitErrMsg,u=r.submitted,d=!!o&&!!l&&!!s
return p.default.createElement(m.Modal,{className:"sign-up-modal ".concat(t?"modal-in-mobile":""),maskClassName:"modal-mask",title:I18N.design.register_account,isOpen:n},u?p.default.createElement("div",{className:"award-view"},p.default.createElement("img",{className:"award",src:"/images/event/award.png"}),p.default.createElement("p",{className:"success-tip"},a.successTip)):p.default.createElement("div",{className:"sign-up-view"},p.default.createElement("p",{className:"event-desc"},a.desc),
p.default.createElement("div",{className:"input-entry"},p.default.createElement(v.default,{className:"icon",type:"mb",name:"user"}),p.default.createElement(m.Input,{className:"input",placeholder:I18N.design.user_name,defaultValue:o,onChange:this.handleFormDataChange("name")})),p.default.createElement("div",{className:"input-entry"},p.default.createElement(v.default,{className:"icon",type:"mb",name:"mail"}),p.default.createElement(m.InputEmail,{className:"input",placeholder:I18N.design.user_email,
defaultValue:l,onChange:this.handleEmailChange})),p.default.createElement("div",{className:"input-entry"},p.default.createElement(v.default,{className:"icon",type:"mb",name:"lock"}),p.default.createElement(m.Input,{className:"input",placeholder:I18N.design.user_password,type:"password",defaultValue:s,onChange:this.handleFormDataChange("pwd")})),!!c&&p.default.createElement("p",{className:"error-msg"},"* ".concat(c)),p.default.createElement(m.Button,{className:"primary-button",type:"primary",isDisabled:!d,
onClick:this.handleSignUp},I18N.design.sign_up),p.default.createElement("p",{className:"agree-terms"},I18N.design.click_register_meant_agree,p.default.createElement("a",{href:"/tos",target:"_blank"},I18N.design.terms_of_service))))}}]),r}(p.PureComponent);(t.default=b).propTypes={event:h.default.object,isOpen:h.default.bool,inMobile:h.default.bool}},"94Et":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.CommentMarkerPanel=void 0
var c=r(n("pVnL")),i=r(n("J4zp")),l=r(n("MVZn")),s=r(n("lwsE")),o=r(n("W8MJ")),u=r(n("a1gu")),d=r(n("Nsbk")),f=r(n("7W2i")),p=r(n("lSNA")),h=a(n("q1tI")),m=r(n("17x9")),v=n("89ER"),g=n("/rSK"),y=n("fiFu"),b="TEMP_MARKER_CID",S=function(e){function n(e){var o;(0,s.default)(this,n),(o=(0,u.default)(this,(0,d.default)(n).call(this,e))).addTempCommentThreadListener=(0,y.muteEvent)(function(e){var t=o.props,n=t.isActive,a=t.permissionPack,r=t.markerDomPack,i=t.dispatch
n&&a.getPermission().create&&w(e,r.getSimulatorContainerElement().getBoundingClientRect())&&i({type:"container:comment:focus-temp-marker",payload:(0,l.default)({},o.markerOperations.getMarkerPosition(e),{cid:b})})})
var t=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:null
return o.props.dispatch({type:"container:comment:focus",payload:{focusCommentThreadCid:e,focusSource:"marker"}})}
return o.markerOperations={addContainerEventListener:function(e){var r=o.props.markerDomPack.getSimulatorContainerElement()
r&&Object.entries(e).forEach(function(e){var t=(0,i.default)(e,2),n=t[0],a=t[1]
return r.addEventListener(n,a)})},removeContainerEventListener:function(e){var r=o.props.markerDomPack.getSimulatorContainerElement()
r&&Object.entries(e).forEach(function(e){var t=(0,i.default)(e,2),n=t[0],a=t[1]
return r.removeEventListener(n,a)})},setFocusCommentThreadCid:t,setHoverFocusCommentThreadCid:function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:null
return!o.props.tempCommentThreadMarker&&t(e)},doUpdateCommentThread:function(e){var t=e.cid,n=e.top,a=e.left
return o.props.dispatch({type:t!==b?"entry:comment-threads:update":"container:comment:focus-temp-marker",payload:{cid:t,top:n,left:a}})},getMarkerPosition:function(e){var t=o.props,n=t.scale,a=t.markerDomPack,r=a.getScreenContainerElement().getBoundingClientRect(),i=a.getSimulatorContainerElement().getBoundingClientRect()
return{left:((0,v.clamp)(e.clientX,i.left+20,i.right-20)-r.left)/n,top:((0,v.clamp)(e.clientY,i.top+20,i.bottom-20)-r.top)/n}}},o}return(0,f.default)(n,e),(0,o.default)(n,[{key:"componentDidMount",value:function(){this.props.isActive&&this.toggleEventListener(!0)}},{key:"componentDidUpdate",value:function(e){var t=this.props.isActive
t!==e.isActive&&this.toggleEventListener(t)}},{key:"componentWillUnmount",value:function(){var e=this.props.dispatch
this.toggleEventListener(!1),e({type:"container:comment:focus-temp-marker",payload:null})}},{key:"toggleEventListener",value:function(e){var t=this.props.markerDomPack.getSimulatorContainerElement()
t&&(e?t.addEventListener("dblclick",this.addTempCommentThreadListener):t.removeEventListener("dblclick",this.addTempCommentThreadListener))}},{key:"render",value:function(){var r=this,e=this.props,t=e.isActive,i=e.scale,o=e.permissionPack,n=e.commentThreadList,a=e.isLoaded,l=e.focusCommentThreadCid,s=e.tempCommentThreadMarker
return t&&a?h.default.createElement("div",null,n.map(function(e,t){var n=Boolean(!s&&l===e.cid),a=Boolean(s||l&&!n)
return h.default.createElement(g.CommentMarker,(0,c.default)({key:e.cid},{commentMarkerIndex:t+1,commentThread:e,scale:i,isEditable:o.getPermission(e.user_id).update,isFocus:n,isFade:a,markerOperations:r.markerOperations}))}),s&&h.default.createElement(g.CommentMarker,{commentMarkerIndex:n.length+1,commentThread:s,scale:i,isEditable:!0,isFocus:!0,isFade:!1,markerOperations:this.markerOperations})):null}}]),n}(h.PureComponent)
t.CommentMarkerPanel=S,(0,p.default)(S,"propTypes",{scale:m.default.number,isActive:m.default.bool,isLoaded:m.default.bool,permissionPack:m.default.object,markerDomPack:m.default.object,commentThreadList:m.default.array,focusCommentThreadCid:m.default.string,tempCommentThreadMarker:m.default.object,dispatch:m.default.func})
var w=function(e,t){var n=t.left,a=t.top,r=t.width,i=t.height
return n<=e.clientX&&a<=e.clientY&&n+r>=e.clientX&&a+i>=e.clientY}},"9ZUU":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=a(n("Hrzm")),o=n("upRB"),l=(0,r.connect)(function(e){var t=(0,o.getRunnerState)(e),n=t.activeCid,a=t.screenInfoMap
return{screenCid:n,stateCid:a[n]&&a[n].stateCid}})(i.default)
t.default=l},Aa0X:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=n("G4qV"),o=n("upRB"),l=n("1iCU"),s=n("pVAx"),c=a(n("dhJN")),u=(0,i.createSelector)([o.getPreference,o.getCurrentMode,o.getIsMultiScreenProject],function(e,t,n){return{toolbarActiveItem:t,isScreenPanelShow:e.layout!==s.CLASSIC&&n,isLayerPanelShow:e.layout===s.CLASSIC&&t===l.INSPECT,isCommentPanelShow:e.layout===s.CLASSIC&&t==l.COMMENT}}),d=(0,r.connect)(function(e){return u(e)})(c.default)
t.default=d},An9T:function(e,t,n){e.exports={shell:"_38-tXAYs8SyeFiNeAicHOH"}},Aq2W:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=function(){return(new Date).getTime()},l=function(){function e(){(0,r.default)(this,e),this.coolDownTime=o(),this.coolDownInterval=200}return(0,i.default)(e,[{key:"isCoolDown",value:function(){var e=o()-this.coolDownTime
return this.coolDownTime+=e,e>this.coolDownInterval}},{key:"resetCoolDown",value:function(){this.coolDownTime-=this.coolDownInterval}}]),e}()
t.default=l},BVfv:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("MVZn")),o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),h=r(n("17x9")),m=n("6XO9"),v=n("wYtL"),g=r(n("m48X")),y=r(n("i6OX")),b=r(n("UbMB")),S=r(n("rj4U")),w=b.default.bind(S.default),E=function(e){function t(e){var a
return(0,o.default)(this,t),a=(0,s.default)(this,(0,c.default)(t).call(this,e)),(0,f.default)((0,u.default)(a),"updateSubToolbar",function(e){a.props.dispatch({type:"reducer:preview-toolbar:update",payload:(0,i.default)({},e)})}),(0,f.default)((0,u.default)(a),"pickColor",function(e){e.nativeEvent.stopImmediatePropagation(),MB.event("preview","在标注模式中使用了自定义取色"),a.updateSubToolbar({isShowColorPicker:!0,showLayerList:!1,isSelectLayer:!1})}),(0,f.default)((0,u.default)(a),"updateDeviceUnit",function(e){
var t=a.props.emPixel,n=N(e,t)
a.updateSubToolbar(n?{unit:e,ratio:n}:{unit:e}),MB.event("preview","在".concat(e,"下切换倍率为").concat(n))}),(0,f.default)((0,u.default)(a),"updateLanguage",function(e){MB.event("preview","代码切换".concat(e)),a.updateSubToolbar({language:e})}),(0,f.default)((0,u.default)(a),"updateColorUnit",function(e){a.updateSubToolbar({colorUnit:e})}),(0,f.default)((0,u.default)(a),"updateEmPixel",function(e){var t=Number(e)
a.updateSubToolbar({emPixel:t,ratio:t}),a.setState({customEmPixel:""})
var n=a.props.unit
MB.event("preview","在".concat(n,"下切换倍率为").concat(t))}),(0,f.default)((0,u.default)(a),"onTypingEmPixel",function(e){if(e){a.setState({customEmPixel:e}),a.updateSubToolbar({emPixel:e,ratio:e})
var t=a.props.unit
MB.event("preview","在".concat(t,"在设置自定义倍率").concat(e))}}),(0,f.default)((0,u.default)(a),"handleMobileChange",function(e){var t=a.props.unit
a.updateSubToolbar({ratio:Number(e)}),MB.event("preview","在".concat(t,"下切换倍率为").concat(e))}),a.state={showLogin:!1,customEmPixel:""},a}return(0,d.default)(t,e),(0,l.default)(t,[{key:"UNSAFE_componentWillReceiveProps",value:function(e){var t=e.unit
this.props.unit!==t&&t===k&&this.updateSubToolbar({ratio:1})}},{key:"render",value:function(){var e=this.props,t=e.unit,n=e.emPixel,a=e.ratio,r=e.language,i=e.isShowColorPicker,o=e.colorUnit,l=e.isLogin,s=this.state.customEmPixel,c=t===x||t===C,u=t===k,d=t===x?I:P,f=[{value:10,label:"10px"},{value:12,label:"12px"},{value:14,label:"14px"},{value:16,label:"16px"},{value:n,label:"".concat(n,"px")},p.default.createElement("div",{onClick:function(e){return e.stopPropagation()}},p.default.createElement(
m.InputNumber,{size:"small",min:1,max:99,precision:0,value:s,placeholder:I18N.custom,onChange:this.onTypingEmPixel}))]
return p.default.createElement("div",{className:w("sub-toolbar","preview-sub-toolbar")},p.default.createElement("div",{className:"mode"},p.default.createElement(y.default,{name:"cursor",type:"dora",className:(0,m.trimList)(["cursor",!i&&"is-active"])}),p.default.createElement(v.Tooltip,{arrowed:!0,position:"bottom",duration:1500,className:(0,m.trimList)(["picker",i&&"is-active"]),tipClassName:"marign-top-20",content:{click:l?null:I18N.preview.guide_login,hover:I18N.preview.color_picker}},
p.default.createElement(y.default,{name:"tube",type:"dora",onClick:this.pickColor}))),p.default.createElement("div",{className:"param"},p.default.createElement(g.default,{className:"color-unit",menuClassName:"PreviewSubToolbarSelectMenu",value:o,optionList:M,onChange:this.updateColorUnit}),p.default.createElement(g.default,{menuClassName:"PreviewSubToolbarSelectMenu",placeholder:" ",optionList:_,value:r,onChange:this.updateLanguage}),p.default.createElement(g.default,{className:"device-unit",
menuClassName:"PreviewSubToolbarSelectMenu",optionList:T,value:t,onChange:this.updateDeviceUnit}),c?p.default.createElement(g.default,{menuClassName:"PreviewSubToolbarSelectMenu",optionList:d,value:a,onChange:this.handleMobileChange}):u?p.default.createElement("span",{className:"px-ratio"},"@1x"):p.default.createElement(g.default,{className:"em-pixel",menuClassName:"PreviewSubToolbarSelectMenu scale-select-menu",optionList:f,value:n,onChange:this.updateEmPixel})))}}]),t}(p.PureComponent)
t.default=E,(0,f.default)(E,"propTypes",{unit:h.default.string,language:h.default.string,ratio:h.default.number,colorUnit:h.default.string,isShowColorPicker:h.default.bool,emPixel:h.default.number,isLogin:h.default.bool,dispatch:h.default.func})
var k="px",C="pt",x="dp",T=[k,"em","rem",x,C],_=[{value:"swift",label:"Swift"},{value:"android",label:"Android"},{value:"css",label:"CSS"},{value:"less",label:"Less"},{value:"sass",label:"Sass"},{value:"stylus",label:"Stylus"}],M=[{value:"hex",label:"Hex"},{value:"rgb",label:"RGB"},{value:"rgba",label:"RGBA"},{value:"argb",label:"ARGB"}],P=[1,2,3].map(function(e){return{value:e,label:"@".concat(e,"x")}}),I=[.75,1,1.5,2,3,4].map(function(e){return{value:e,label:"@".concat(e,"x")}}),N=function(e,t){
return"em"===e||"rem"===e?t:1}},CWx7:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.runnerEntry=void 0
var d=a(n("QILm")),y=a(n("MVZn")),g=a(n("RIqP")),b=a(n("lSNA")),S=n("upRB"),w=n("RKRO"),E=function(t){var n={},a={}
return Panel.all().forEach(function(e){e.screen_cid===t&&(e.multi_states?a[e.cid]=C(e):n[e.cid]=k(e))}),Screen.find(t).setState("default",!0),{cid:t,stateCid:"default",panelInfoMap:n,chameleonInfoMap:a}},k=function(e){var t=e.mainState().cid
return{cid:e.cid,activeScreenCid:t,panelScreens:[t]}},C=function(e,t){var n=e.ct().homeScreen(),a=e.mainState().cid
return n.setState(a,!0),{cid:e.cid,stateCid:e.mainState().cid,transition:t}},r={"entry:runner:init:home-screen":function(e,t){var n=e.dispatch,a=t.payload.activeCid
n({type:"runner:update:state",payload:{transition:{name:"none",delay:0,duration:0,offset:100},screenInfoMap:(0,b.default)({},a,E(a)),history:[]}})},"entry:runner:reload:screen":function(e,t){var n=e.dispatch,a=t.payload.activeCid
n({type:"entry:runner:init:home-screen",payload:{activeCid:a}}),n({type:"entry:runner:activate:screen",payload:{screenCid:a}})},"entry:runner:activate:screen":function(e,t){var n=e.getState,a=e.dispatch,r=t.payload,i=r.screenCid,o=r.transition,l=r.resetTargetScreen,s=void 0===l||l,c=n(),u=(0,S.getRunnerState)(c),d=u.activeCid,f=u.screenInfoMap,p=u.history;/drawer|menu/.test((o=o||{name:"none",delay:0,duration:0,offset:100}).name)?(MB.runner.currentScreen=d,MB.runner.currentMenu=i
):MB.runner.currentScreen=MB.runner.currentMenu=null
var h=[i].concat((0,g.default)(p.filter(function(e){return e!==i}))),m=f[i],v=m&&!s?m:E(i)
s&&MB.runner.runnerUtil.resetScreenScrollState(i),a({type:"runner:update:state",payload:{transition:o,screenInfoMap:(0,y.default)({},f,(0,b.default)({},i,v)),activeCid:i,history:h}})},"entry:runner:activate:screen-state":function(e,t){var n=e.getState,a=e.dispatch,r=t.payload,i=r.screenCid,o=r.stateCid,l=r.transition,s=n(),c=(0,S.getRunnerState)(s),u=c.activeCid,d=c.screenInfoMap
if(u===i&&d[u].stateCid!==o){var f=Screen.find(u),p=f.height-(f.headerHeight()+f.footerHeight())
f.setState(o,!0)
var h=f.height-(f.headerHeight()+f.footerHeight()),m=(0,y.default)({},l,{callback:function(){console.log("状态切换完成"),p!=h&&MB.runner.runnerUtil.renderScrollbar(u),MB.runner.timerHandler.setupPageTimers(f,o)}}),v={},g={}
f.cpanels().forEach(function(e){var t=Panelstate.find(o+e.cid)||e
t.cid=e.cid,t.screen_cid=f.cid,t.multi_states=e.multi_states,t.template_cid=e.template_cid,t.multi_states?g[e.cid]=C(t,l):v[e.cid]=k(t)}),a({type:"entry:runner:update:screen",payload:{screenCid:i,stateCid:o,panelInfoMap:v,chameleonInfoMap:g,transition:m}})}},"entry:runner:back-to-prev-page":function(e,t){var n=e.getState,a=e.dispatch,r=t.payload,i=void 0===r?{}:r,o=n(),l=(0,S.getRunnerState)(o),s=l.history,c=l.transition,u=c.name,d=c.duration,f=c.offset
if(1!==s.length){var p,h=Screen.find(s[0]),m=Screen.find(s[1])
p=h.orient()!==m.orient()?{name:"none",delay:0,duration:0,offset:100}:i.transition?i.transition:{name:(0,w.getReverseTransitionName)(u),delay:0,duration:d,offset:f,callback:i.callback}
var v=s.slice(1)
a({type:"runner:update:state",payload:{activeCid:v[0],transition:p,history:v}})}},"entry:runner:update:screen":function(e,t){var n=e.getState,a=e.dispatch,r=t.payload,i=r.screenCid,o=(0,d.default)(r,["screenCid"])
console.log("entry:runner:update:screen",i,o)
var l=n(),s=(0,S.getRunnerState)(l).screenInfoMap,c=s[i]
if(!c)throw new Error("更新了尚未加载的页面!!")
var u=(0,y.default)({},c,o)
a({type:"runner:update:state",payload:{screenInfoMap:(0,y.default)({},s,(0,b.default)({},i,u))}})},"entry:runner:activate:panel-screen":function(e,t){var n=e.getState,a=e.dispatch,r=t.payload,i=r.panelCid,o=r.panelScreenCid,l=r.transition,s=n(),c=(0,S.getRunnerState)(s).screenInfoMap,u=Panel.find(i).screen_cid,d=c[u],f=d.panelInfoMap[i],p=new Set(f.panelScreens)
p.add(o)
var h=(0,y.default)({},f,{transition:l,activeScreenCid:o,panelScreens:Array.from(p)}),m=(0,y.default)({},d,{panelInfoMap:(0,y.default)({},d.panelInfoMap,(0,b.default)({},i,h))})
a({type:"runner:update:state",payload:{screenInfoMap:(0,y.default)({},c,(0,b.default)({},u,m))}})},"entry:runner:preload:screens":function(e){var t=e.getState,n=e.dispatch,a=t(),r=(0,S.getCurrentProject)(a),i=(0,S.getRunnerState)(a),o=i.activeCid,l=i.screenInfoMap,s=i.history.slice(0,2)
Link.all().forEach(function(e){if(e.target_cid&&e.screen_cid===o&&"none"!==e.transition&&"prev"!==e.target_cid){var t=Screen.find(e.target_cid)
t&&t.project_cid===r.cid&&s.push(e.target_cid)}})
var c={}
s.forEach(function(e){c[e]=l[e]||E(e)}),n({type:"runner:update:state",payload:{screenInfoMap:c}})},"entry:runner:update:chameleon":function(e,t){var n=e.getState,a=e.dispatch,r=t.payload,i=r.chameleonCid,o=r.stateCid,l=r.transition,s=n(),c=(0,S.getRunnerState)(s).screenInfoMap,u=Panel.find(i),d=u.screen_cid,f=c[d],p=f.chameleonInfoMap[i],h=(0,y.default)({},p,{stateCid:o,transition:(0,y.default)({},l,{callback:function(){MB.runner.timerHandler.setupPanelTimers(u,o)}})}),m=(0,y.default)({},f,{
chameleonInfoMap:(0,y.default)({},f.chameleonInfoMap,(0,b.default)({},i,h))})
a({type:"runner:update:state",payload:{screenInfoMap:(0,y.default)({},c,(0,b.default)({},d,m))}})}}
t.runnerEntry=r},DJvY:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=a(n("4WDG")),c=n("upRB"),o=(0,r.connect)(function(e){var t=e.container,n=t.common,a=n.offset,r=n.keyFlags.isSpaceDown,i=t.previewSetting,o=i.toolbarActiveItem,l=i.isShowColorPicker,s=i.isFullScreenMode
return{scale:(0,c.getCurrentScale)(e),canvasOffset:a,screen:(0,c.getCurrentScreen)(e),project:(0,c.getCurrentProject)(e),shellType:(0,c.getShellType)(e),isSpaceDown:r,isStickyShow:(0,c.getIsStickyShow)(e),isScrollable:(0,c.getIsScrollable)(e),isLayerPreview:"preview"==o,isLayerActive:"inspect"==o,isCommentActive:"comment"==o,isFullScreenMode:s,isColorPickerActive:l}})(i.default)
t.default=o},DdUa:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var f=a(n("J4zp")),r=n("/MKj"),p=n("upRB"),i=a(n("m/Xg")),o=(0,r.connect)(function(e){var t=(0,p.getCurrentScreen)(e),n=(0,p.getCurrentProject)(e),a=(0,p.getIsImmersive)(e),r=(0,p.getIsScrollable)(e),i=a||!r,o=MB.isMobile(),l=MB.isEmbedded(),s=o||l,c=l&&"landscape"===Project.find(n.cid).homeScreen().orientation?[n.height,n.width]:[n.width,n.height],u=l?c:[window.innerWidth,window.innerHeight],d=(0,f.default)(u,2)
return{screen:t,project:n,isLite:s,isImmersive:a,isScreenExpanded:i,viewportWidth:d[0],viewportHeight:d[1]}})(i.default)
t.default=o},DqDi:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.NavigationBar=t.NavItem=t.default=void 0
var o=r(n("PJYZ")),l=r(n("lwsE")),s=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=r(n("i6OX")),m=r(n("UbMB")),v=r(n("G916")),g=m.default.bind(v.default)
var y=function(e){function t(){return(0,l.default)(this,t),(0,c.default)(this,(0,u.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,s.default)(t,[{key:"render",value:function(){var e=this.props,a=e.activeIndex,t=e.hideBorder,n=e.className,r=e.children,i=e.onTabChange,o=function(e,t,n){var a=0===e,r=e===t-1
return{transform:"translateX(".concat(100*e,"%)"),borderLeftColor:n&&a?"transparent":"",borderRightColor:n&&r?"transparent":""}}(a,p.Children.count(r),t)
return p.default.createElement("ol",{type:"slide-nav",className:g("nav",n)},p.Children.map(r,function(e,t){var n={index:t,active:t===a,BgStyle:0===t?o:null,onClick:i}
return p.default.cloneElement(e,n)}))}}]),t}(p.PureComponent)
t.default=y,(0,f.default)(y,"propTypes",{className:i.default.string,activeIndex:i.default.number,hideBorder:i.default.bool,children:i.default.array,onTabChange:i.default.func}),(0,f.default)(y,"defaultProps",{hideBorder:!1,activeIndex:0})
var b=function(e){function i(){var e,a;(0,l.default)(this,i)
for(var t=arguments.length,n=new Array(t),r=0;r<t;r++)n[r]=arguments[r]
return a=(0,c.default)(this,(e=(0,u.default)(i)).call.apply(e,[this].concat(n))),(0,f.default)((0,o.default)(a),"handleClick",function(e){var t=a.props,n=t.index;(0,t.onClick)(n)}),a}return(0,d.default)(i,e),(0,s.default)(i,[{key:"render",value:function(){var e=this.props,t=e.index,n=e.active,a=e.icon,r=e.label,i=e.title,o=e.BgStyle,l=e.dataHtml
return p.default.createElement("li",{className:g("nav-item",{active:n}),"data-html":l,title:i,onClick:this.handleClick},0===t&&p.default.createElement("div",{className:"background-cube",style:o}),a&&p.default.createElement("div",{className:"nav-icon"},"string"==typeof a?p.default.createElement(h.default,{type:"dora",name:a}):a),r&&p.default.createElement("span",{className:"nav-label"},r))}}]),i}(p.PureComponent)
t.NavItem=b,(0,f.default)(b,"propTypes",{index:i.default.number,icon:i.default.oneOfType([i.default.string,i.default.object]),title:i.default.string,label:i.default.string,dataHtml:i.default.string,active:i.default.bool,BgStyle:i.default.object,onClick:i.default.func})
var S=function(e){var t=e.tabs,n=e.activeIndex,a=e.onChange,r=e.className,i=e.hideBorder,o=e.BgStyle
return p.default.createElement(y,{activeIndex:n,hideBorder:i,onTabChange:a,className:r},t.map(function(e){var t=e.label,n=e.icon
return p.default.createElement(b,{key:t,icon:n,label:t,BgStyle:o})}))};(t.NavigationBar=S).propTypes={tabs:i.default.array,activeIndex:i.default.number,onChange:i.default.func,className:i.default.string,hideBorder:i.default.bool,BgStyle:i.default.object}},EDI8:function(e,t,n){e.exports={"zoom-count":"_3bJjkHIbbJ3_hpAgUkjNFN"}},ER7e:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),d=r(n("17x9")),f=a(n("q1tI")),p=n("i6OX")
n("peLG")
var h=function(e){function t(){return(0,i.default)(this,t),(0,l.default)(this,(0,s.default)(t).apply(this,arguments))}return(0,c.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){return f.default.createElement("div",{className:"top-right-action"},f.default.createElement("div",{className:"mode"},f.default.createElement(p.SVGIcon,{name:"design/preview/daynight"}),f.default.createElement("span",{className:"light","data-mode":"light",onClick:this.props.onClickMode}),f.default.createElement("span",{
className:"dark","data-mode":"dark",onClick:this.props.onClickMode})),f.default.createElement("div",{className:"exit-full-screen",onClick:this.props.onClickExit},f.default.createElement(p.SVGIcon,{name:"design/preview/exit"})))}}]),t}(f.PureComponent)
t.default=h,(0,u.default)(h,"propTypes",{onClickMode:d.default.func,onClickExit:d.default.func})},EWR0:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("NcbO")),m=r(n("GWLA")),v=r(n("YCqe")),g=r(n("UbMB")).default.bind(v.default),y=function(e){function t(){var n
return(0,i.default)(this,t),n=(0,l.default)(this,(0,s.default)(t).call(this)),(0,d.default)((0,c.default)(n),"handleTabClick",function(e){var t=Number(e.target.dataset.index)
n.setState({tabIndex:t})}),n.state={isShow:!1,tabIndex:1},MB.debugRunner=function(){return n.setState({isShow:!n.state.isShow})},n}return(0,u.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.runnerState,n=e.dispatch,a=this.state,r=a.isShow,i=a.tabIndex
return r?p.default.createElement("div",{className:g("debug-panel")},p.default.createElement("ul",{className:"tab"},p.default.createElement("li",{"data-index":"0",className:g({active:0===i}),onClick:this.handleTabClick},"状态"),p.default.createElement("li",{"data-index":"1",className:g({active:1===i}),onClick:this.handleTabClick},"控制")),p.default.createElement("div",{className:"content"},0===i&&p.default.createElement(h.default,{runnerState:t,dispatch:n}),1===i&&p.default.createElement(m.default,{dispatch:n}))
):null}}]),t}(p.PureComponent)
t.default=y,(0,d.default)(y,"propTypes",{runnerState:f.default.object,dispatch:f.default.func})},Ehhz:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.MODEL_OPERATION_MAP=void 0
var s=a(n("MVZn")),r=a(n("RIqP")),c=n("Saem"),u=a(n("zkrS")),d=u.default.SpineModel,f={Team:"t",Project:"p",Combo:"c",Template:"t",UserTemplate:"ut",Screen:"s",Collaborator:"co",Comment:"cm",CommentThread:"cmth",Widget:"w"},i=Object.keys(f),p=i.reduce(function(e,t){return e[t]=d[t].attributes,e},{})
p.Widget=[].concat((0,r.default)(p.Widget),["id"])
var o=i.reduce(function(e,t){var i=d[t],a=p[t],o=f[t],l=function(e,t){return{dataState:e.find(function(e){return e.cid===t}),dataModel:i.findByAttribute("cid",t)}}
return e[t]={refreshStateList:function(e){return i.all().map(function(e){return function(t){var n=1<arguments.length&&void 0!==arguments[1]?arguments[1]:{}
return a.forEach(function(e){return n[e]=t[e]}),n}(e,{})})},saveState:function(e,t,n){var a=t.cid,r=l(e,a),i=r.dataState,o=r.dataModel
return i&&o&&(o.lsave(!n),!n&&u.default.SpineModel.queueSave()),e},addState:function(e,t,n){var a=t.cid||u.default.SpineModel.requestCid(o);(function(e,t){var n=e.find(function(e){return e.cid===t}),a=i.findByAttribute("cid",t)
return Boolean(n||a)})(e,a)&&(a=u.default.SpineModel.requestCid(o))
var r=(0,s.default)({},t,{cid:a})
return new i(r).lsave(!n),!n&&u.default.SpineModel.queueSave(),(0,c.arrayPush)(e,r)},updateState:function(e,t,n){var a=t.cid,r=l(e,a),i=r.dataState,o=r.dataModel
return i&&o?(i=(0,s.default)({},i,t),Object.assign(o,i),o.lsave(!n),!n&&u.default.SpineModel.queueSave(),(0,c.arrayFindSet)(e,function(e){return e.cid===a},i)):e},deleteState:function(e,t,n){var a=t.cid,r=l(e,a),i=r.dataState,o=r.dataModel
return i&&o?(o.ldestroy(!n),!n&&u.default.SpineModel.queueSave(),(0,c.arrayFindDelete)(e,function(e){return e.cid===a})):e}},e},{}),l=function(i){return function(e,t,n){var a=t.cid,r=d.Project.findByAttribute("cid",a)?"Project":d.Template.findByAttribute("cid",a)?"Template":d.Combo.findByAttribute("cid",a)?"Combo":null
return o[r][i](e,t,n)}};(t.MODEL_OPERATION_MAP=o).ProjectAlike={refreshStateList:function(e){return[].concat((0,r.default)(o.Combo.refreshStateList()),(0,r.default)(o.Project.refreshStateList()),(0,r.default)(o.Template.refreshStateList()),(0,r.default)(o.UserTemplate.refreshStateList()))},saveState:l("saveState"),addState:l("addState"),updateState:l("updateState"),deleteState:l("deleteState")}},Emwt:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("WVP6"),r=n("Ehhz").MODEL_OPERATION_MAP.Screen,i=(0,a.createStateStore)([]),o=i.getState,l=i.setState,s=i.wrapEntry,c=function(i,o){return s(function(e,t,n){var a=t.dispatch,r=n&&n.payload
a({type:"reducer:screens:update",payload:i(e,r,o)})})},u={entryMap:{"screens:refresh":c(r.refreshStateList,!1),"screens:add":c(r.addState,!1),"screens:add-local":c(r.addState,!0),"screens:update":c(r.updateState,!1),"screens:update-local":c(r.updateState,!0),"screens:delete":c(r.deleteState,!1),"screens:delete-local":c(r.deleteState,!0)},getState:o,setState:l}
t.default=u},"FC/4":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.TextEditComponent=t.createTextEditStore=t.INITIAL_STATE=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),d=r(n("MVZn")),f=a(n("q1tI")),p=r(n("17x9")),h=r(n("vOnD")),m=n("6XO9"),v=n("n2S4"),g={value:"",startValue:"",isEditing:!1}
t.INITIAL_STATE=g
t.createTextEditStore=function(e,t){var n=t.onStart,a=t.onChange,r=t.onEnd;(e=(0,d.default)({},g,e)).startValue=e.value
var i=(0,v.createStateStore)(e),o=i.subscribe,l=i.unsubscribe,s=i.getState,c=i.setState
return{subscribe:o,unsubscribe:l,getState:s,startEdit:function(){c({isEditing:!0}),n&&n(s()),c({startValue:s().value})},endEdit:function(){c({isEditing:!1}),r&&r(s())},setValue:function(e){s().isEditing&&(c({value:e}),a&&a(s()))}}}
var y=function(e){function r(e){var n;(0,i.default)(this,r),n=(0,l.default)(this,(0,s.default)(r).call(this,e))
var t=function(e,t){n.setState(e),!t.isEditing&&e.isEditing&&setTimeout(n.focusTextarea,0)}
n.bindEditStore=function(e){n.setState(e.getState()),e.subscribe(t)},n.unbindEditStore=function(e){e.unsubscribe(t)},n.onChange=function(e){return n.props.textEditStore.setValue(e)},n.onKeyDown=function(e){("Enter"===e.key||13===e.which)&&(!n.props.multiline||!e.shiftKey)&&(e.preventDefault(),e.stopPropagation(),n.props.textEditStore.endEdit())}
var a=null
return n.setRef=function(e){a=e&&e.querySelector("textarea")},n.focusTextarea=function(){if(a){a.focus&&a.focus()
var e=a.value.length
a.setSelectionRange(e,e)}},n.autoHeightTextarea=function(){n.props.autoHeight&&a&&(a.style.height="auto",a.style.height="".concat(Math.max(a.scrollHeight+2,a.offsetHeight,n.props.minHeight),"px"))},n}return(0,c.default)(r,e),(0,o.default)(r,[{key:"componentDidMount",value:function(){this.bindEditStore(this.props.textEditStore),this.focusTextarea()}},{key:"componentDidUpdate",value:function(e){this.props.textEditStore!==e.textEditStore&&(this.unbindEditStore(e.textEditStore),this.bindEditStore(
this.props.textEditStore)),this.autoHeightTextarea()}},{key:"render",value:function(){var e=this.props,t=e.placeholder,n=void 0===t?"":t,a=e.textEditStore.getState().value
return f.default.createElement(b,{ref:this.setRef},f.default.createElement(m.Textarea,{value:a,placeholder:n,rows:1,onChange:this.onChange,onKeyDown:this.onKeyDown}))}}]),r}(f.PureComponent)
t.TextEditComponent=y,(0,u.default)(y,"propTypes",{textEditStore:p.default.object.isRequired,placeholder:p.default.string,multiline:p.default.bool,autoHeight:p.default.bool,minHeight:p.default.number})
var b=h.default.div.withConfig({displayName:"TextEditComponent__HackStyleDiv",componentId:"sc-1wltfay-0"})(["&&& label{width:100%;}&&& textarea{font-size:12px;resize:none;}"])},FJlG:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:s,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"reducer:preview-toolbar:update":return(0,r.default)({},e,a)
case"reducer:preview-toolbar:active-item:init":return(0,r.default)({},e,{toolbarActiveItem:i.PREVIEW,shellType:(0,l.localStorageGetItem)("preview-shell-type-".concat(MB.currentProject.cid))||MB.currentProject.shell_type})
case"reducer:preview-toolbar:fullscreen":return(0,r.default)({},e,{isFullScreenMode:a.isFullScreenMode})
case"reducer:preview-toolbar:update:highlight":return(0,r.default)({},e,{isHighlight:a.isHighlight})
default:return e}}
var r=a(n("MVZn")),i=n("1iCU"),o=n("/5+U"),l=n("7Qib"),s={ratio:1,emPixel:16,unit:"px",colorUnit:"hex",language:"css",toolbarActiveItem:i.PREVIEW,isShowColorPicker:!1,isSelectLayer:!1,userPickColor:(0,o.getHistoryColor)(),focusColor:null,loadSliceUrl:"",isFullScreenMode:!1,isScrollable:!0,isStickyShow:!0,isHighlight:!0,shellType:"device"}},FTTL:function(e,t,n){"use strict"
var c=n("TqRt")(n("cDf5"))
!function(i,o,f){var h=i.requestAnimationFrame||i.webkitRequestAnimationFrame||i.mozRequestAnimationFrame||i.oRequestAnimationFrame||i.msRequestAnimationFrame||function(e){i.setTimeout(e,1e3/60)},m=function(){var a={},r=o.createElement("div").style,t=function(){for(var e=["t","webkitT","MozT","msT","OT"],t=0,n=e.length;t<n;t++)if(e[t]+"ransform"in r)return e[t].substr(0,e[t].length-1)
return!1}()
function e(e){return!1!==t&&(""===t?e:t+e.charAt(0).toUpperCase()+e.substr(1))}a.getTime=Date.now||function(){return(new Date).getTime()},a.extend=function(e,t){for(var n in t)e[n]=t[n]},a.addEvent=function(e,t,n,a){e.addEventListener(t,n,!!a)},a.removeEvent=function(e,t,n,a){e.removeEventListener(t,n,!!a)},a.prefixPointerEvent=function(e){return i.MSPointerEvent?"MSPointer"+e.charAt(7).toUpperCase()+e.substr(8):e},a.momentum=function(e,t,n,a,r,i){var o,l,s=e-t,c=f.abs(s)/n
return l=c/(i=void 0===i?6e-4:i),(o=e+c*c/(2*i)*(s<0?-1:1))<a?(o=r?a-r/2.5*(c/8):a,l=(s=f.abs(o-e))/c):0<o&&(o=r?r/2.5*(c/8):0,l=(s=f.abs(e)+o)/c),{destination:f.round(o),duration:l}}
var n=e("transform")
return a.extend(a,{hasTransform:!1!==n,hasPerspective:e("perspective")in r,hasTouch:"ontouchstart"in i,hasPointer:!(!i.PointerEvent&&!i.MSPointerEvent),hasTransition:e("transition")in r}),a.isBadAndroid=function(){var e=i.navigator.appVersion
if(!/Android/.test(e)||/Chrome\/\d/.test(e))return!1
var t=e.match(/Safari\/(\d+.\d)/)
return!(t&&"object"===(0,c.default)(t)&&2<=t.length)||parseFloat(t[1])<535.19}(),a.extend(a.style={},{transform:n,transitionTimingFunction:e("transitionTimingFunction"),transitionDuration:e("transitionDuration"),transitionDelay:e("transitionDelay"),transformOrigin:e("transformOrigin"),touchAction:e("touchAction")}),a.hasClass=function(e,t){return new RegExp("(^|\\s)"+t+"(\\s|$)").test(e.className)},a.addClass=function(e,t){if(!a.hasClass(e,t)){var n=e.className.split(" ")
n.push(t),e.className=n.join(" ")}},a.removeClass=function(e,t){if(a.hasClass(e,t)){var n=new RegExp("(^|\\s)"+t+"(\\s|$)","g")
e.className=e.className.replace(n," ")}},a.offset=function(e){for(var t=-e.offsetLeft,n=-e.offsetTop;e=e.offsetParent;)t-=e.offsetLeft,n-=e.offsetTop
return{left:t,top:n}},a.preventDefaultException=function(e,t){for(var n in t)if(t[n].test(e[n]))return!0
return!1},a.extend(a.eventType={},{touchstart:1,touchmove:1,touchend:1,mousedown:2,mousemove:2,mouseup:2,pointerdown:3,pointermove:3,pointerup:3,MSPointerDown:3,MSPointerMove:3,MSPointerUp:3}),a.extend(a.ease={},{quadratic:{style:"cubic-bezier(0.25, 0.46, 0.45, 0.94)",fn:function(e){return e*(2-e)}},circular:{style:"cubic-bezier(0.1, 0.57, 0.1, 1)",fn:function(e){return f.sqrt(1- --e*e)}},back:{style:"cubic-bezier(0.175, 0.885, 0.32, 1.275)",fn:function(e){return(e-=1)*e*(5*e+4)+1}},bounce:{style:"",
fn:function(e){return(e/=1)<1/2.75?7.5625*e*e:e<2/2.75?7.5625*(e-=1.5/2.75)*e+.75:e<2.5/2.75?7.5625*(e-=2.25/2.75)*e+.9375:7.5625*(e-=2.625/2.75)*e+.984375}},elastic:{style:"",fn:function(e){return 0===e?0:1==e?1:.4*f.pow(2,-10*e)*f.sin((e-.055)*(2*f.PI)/.22)+1}}}),a.tap=function(e,t){var n=o.createEvent("Event")
n.initEvent(t,!0,!0),n.pageX=e.pageX,n.pageY=e.pageY,e.target.dispatchEvent(n)},a.click=function(e){var t,n=e.target;/(SELECT|INPUT|TEXTAREA)/i.test(n.tagName)||((t=o.createEvent(i.MouseEvent?"MouseEvents":"Event")).initEvent("click",!0,!0),t.view=e.view||i,t.detail=1,t.screenX=n.screenX||0,t.screenY=n.screenY||0,t.clientX=n.clientX||0,t.clientY=n.clientY||0,t.ctrlKey=!!e.ctrlKey,t.altKey=!!e.altKey,t.shiftKey=!!e.shiftKey,t.metaKey=!!e.metaKey,t.button=0,t.relatedTarget=null,t._constructed=!0,
n.dispatchEvent(t))},a.getTouchAction=function(e,t){var n="none"
return"vertical"===e?n="pan-y":"horizontal"===e&&(n="pan-x"),t&&"none"!=n&&(n+=" pinch-zoom"),n},a.getRect=function(e){if(e instanceof SVGElement){var t=e.getBoundingClientRect()
return{top:t.top,left:t.left,width:t.width,height:t.height}}return{top:e.offsetTop,left:e.offsetLeft,width:e.offsetWidth,height:e.offsetHeight}},a}()
function e(e,t){for(var n in this.wrapper="string"==typeof e?o.querySelector(e):e,this.scroller=this.wrapper.children[0],this.scrollerStyle=this.scroller.style,this.options={resizeScrollbars:!0,mouseWheelSpeed:20,snapThreshold:.334,disablePointer:!m.hasPointer,disableTouch:m.hasPointer||!m.hasTouch,disableMouse:m.hasPointer||m.hasTouch,startX:0,startY:0,scrollY:!0,directionLockThreshold:5,momentum:!0,bounce:!0,bounceTime:600,bounceEasing:"",preventDefault:!0,preventDefaultException:{
tagName:/^(INPUT|TEXTAREA|BUTTON|SELECT)$/},HWCompositing:!0,useTransition:!0,useTransform:!0,bindToWrapper:void 0===i.onmousedown},t)this.options[n]=t[n]
this.translateZ=this.options.HWCompositing&&m.hasPerspective?" translateZ(0)":"",this.options.useTransition=m.hasTransition&&this.options.useTransition,this.options.useTransform=m.hasTransform&&this.options.useTransform,this.options.eventPassthrough=!0===this.options.eventPassthrough?"vertical":this.options.eventPassthrough,this.options.preventDefault=!this.options.eventPassthrough&&this.options.preventDefault,this.options.scrollY="vertical"!=this.options.eventPassthrough&&this.options.scrollY,
this.options.scrollX="horizontal"!=this.options.eventPassthrough&&this.options.scrollX,this.options.freeScroll=this.options.freeScroll&&!this.options.eventPassthrough,this.options.directionLockThreshold=this.options.eventPassthrough?0:this.options.directionLockThreshold,this.options.bounceEasing="string"==typeof this.options.bounceEasing?m.ease[this.options.bounceEasing]||m.ease.circular:this.options.bounceEasing,this.options.resizePolling=void 0===this.options.resizePolling?60:this.options.resizePolling,
!0===this.options.tap&&(this.options.tap="tap"),this.options.useTransition||this.options.useTransform||/relative|absolute/i.test(this.scrollerStyle.position)||(this.scrollerStyle.position="relative"),"scale"==this.options.shrinkScrollbars&&(this.options.useTransition=!1),this.options.invertWheelDirection=this.options.invertWheelDirection?-1:1,3==this.options.probeType&&(this.options.useTransition=!1),this.x=0,this.y=0,this.directionX=0,this.directionY=0,this._events={},this._init(),this.refresh(),
this.scrollTo(this.options.startX,this.options.startY),this.enable()}function l(e,t,n){var a=o.createElement("div"),r=o.createElement("div")
return!0===n&&(a.style.cssText="position:absolute;z-index:9999",r.style.cssText="-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box;position:absolute;background:rgba(0,0,0,0.5);border:1px solid rgba(255,255,255,0.9);border-radius:3px"),r.className="iScrollIndicator","h"==e?(!0===n&&(a.style.cssText+=";height:7px;left:2px;right:2px;bottom:0",r.style.height="100%"),a.className="iScrollHorizontalScrollbar"):(!0===n&&(a.style.cssText+=";width:7px;bottom:2px;top:2px;right:1px",
r.style.width="100%"),a.className="iScrollVerticalScrollbar"),a.style.cssText+=";overflow:hidden",t||(a.style.pointerEvents="none"),a.appendChild(r),a}function s(e,t){for(var n in this.wrapper="string"==typeof t.el?o.querySelector(t.el):t.el,this.wrapperStyle=this.wrapper.style,this.indicator=this.wrapper.children[0],this.indicatorStyle=this.indicator.style,this.scroller=e,this.options={listenX:!0,listenY:!0,interactive:!1,resize:!0,defaultScrollbars:!1,shrink:!1,fade:!1,speedRatioX:0,speedRatioY:0},t
)this.options[n]=t[n]
if(this.sizeRatioX=1,this.sizeRatioY=1,this.maxPosX=0,this.maxPosY=0,this.options.interactive&&(this.options.disableTouch||(m.addEvent(this.indicator,"touchstart",this),m.addEvent(i,"touchend",this)),this.options.disablePointer||(m.addEvent(this.indicator,m.prefixPointerEvent("pointerdown"),this),m.addEvent(i,m.prefixPointerEvent("pointerup"),this)),this.options.disableMouse||(m.addEvent(this.indicator,"mousedown",this),m.addEvent(i,"mouseup",this))),this.options.fade){
this.wrapperStyle[m.style.transform]=this.scroller.translateZ
var a=m.style.transitionDuration
if(!a)return
this.wrapperStyle[a]=m.isBadAndroid?"0.0001ms":"0ms"
var r=this
m.isBadAndroid&&h(function(){"0.0001ms"===r.wrapperStyle[a]&&(r.wrapperStyle[a]="0s")}),this.wrapperStyle.opacity="0"}}e.prototype={version:"5.2.0-snapshot",_init:function(){this._initEvents(),(this.options.scrollbars||this.options.indicators)&&this._initIndicators(),this.options.mouseWheel&&this._initWheel(),this.options.snap&&this._initSnap(),this.options.keyBindings&&this._initKeys()},destroy:function(){this._initEvents(!0),clearTimeout(this.resizeTimeout),this.resizeTimeout=null,this._execEvent(
"destroy")},_transitionEnd:function(e){e.target==this.scroller&&this.isInTransition&&(this._transitionTime(),this.resetPosition(this.options.bounceTime)||(this.isInTransition=!1,this._execEvent("scrollEnd")))},_start:function(e){if(1!=m.eventType[e.type]&&0!==(e.which?e.button:e.button<2?0:4==e.button?1:2))return
if(this.enabled&&(!this.initiated||m.eventType[e.type]===this.initiated)&&(!this.options.ignoreEventException||!this.options.ignoreEventException(e))){!this.options.preventDefault||m.isBadAndroid||m.preventDefaultException(e.target,this.options.preventDefaultException)||e.preventDefault()
var t,n=e.touches?e.touches[0]:e
this.initiated=m.eventType[e.type],this.moved=!1,this.distX=0,this.distY=0,this.directionX=0,this.directionY=0,this.directionLocked=0,this.startTime=m.getTime(),this.options.useTransition&&this.isInTransition?(this._transitionTime(),this.isInTransition=!1,t=this.getComputedPosition(),this._translate(f.round(t.x),f.round(t.y)),this._execEvent("scrollEnd")):!this.options.useTransition&&this.isAnimating&&(this.isAnimating=!1,this._execEvent("scrollEnd")),this.startX=this.x,this.startY=this.y,
this.absStartX=this.x,this.absStartY=this.y,this.pointX=n.pageX,this.pointY=n.pageY,this._execEvent("beforeScrollStart")}},_move:function(e){if(this.enabled&&m.eventType[e.type]===this.initiated&&(!this.options.ignoreEventException||!this.options.ignoreEventException(e))){this.options.preventDefault&&e.preventDefault()
var t,n,a,r,i=e.touches?e.touches[0]:e,o=i.pageX-this.pointX,l=i.pageY-this.pointY,s=m.getTime()
if(this.pointX=i.pageX,this.pointY=i.pageY,this.distX+=o,this.distY+=l,a=f.abs(this.distX),r=f.abs(this.distY),!(300<s-this.endTime&&a<10&&r<10)){if(this.directionLocked||this.options.freeScroll||(a>r+this.options.directionLockThreshold?this.directionLocked="h":r>=a+this.options.directionLockThreshold?this.directionLocked="v":this.directionLocked="n"),"h"==this.directionLocked){if("vertical"==this.options.eventPassthrough)e.preventDefault()
else if("horizontal"==this.options.eventPassthrough)return void(this.initiated=!1)
l=0}else if("v"==this.directionLocked){if("horizontal"==this.options.eventPassthrough)e.preventDefault()
else if("vertical"==this.options.eventPassthrough)return void(this.initiated=!1)
o=0}o=this.hasHorizontalScroll?o:0,l=this.hasVerticalScroll?l:0,t=this.x+o,n=this.y+l,(0<t||t<this.maxScrollX)&&(t=this.options.bounce?this.x+o/3:0<t?0:this.maxScrollX),(0<n||n<this.maxScrollY)&&(n=this.options.bounce?this.y+l/3:0<n?0:this.maxScrollY),this.directionX=0<o?-1:o<0?1:0,this.directionY=0<l?-1:l<0?1:0,this.moved||this._execEvent("scrollStart"),this.moved=!0,this._translate(t,n),300<s-this.startTime&&(this.startTime=s,this.startX=this.x,this.startY=this.y,
1==this.options.probeType&&this._execEvent("scroll")),1<this.options.probeType&&this._execEvent("scroll")}}},_end:function(e){if(this.enabled&&m.eventType[e.type]===this.initiated){this.options.preventDefault&&!m.preventDefaultException(e.target,this.options.preventDefaultException)&&e.preventDefault()
e.changedTouches&&e.changedTouches[0]
var t,n,a=m.getTime()-this.startTime,r=f.round(this.x),i=f.round(this.y),o=f.abs(r-this.startX),l=f.abs(i-this.startY),s=0,c=""
if(this.isInTransition=0,this.initiated=0,this.endTime=m.getTime(),!this.resetPosition(this.options.bounceTime)){if(this.scrollTo(r,i),!this.moved)return this.options.tap&&m.tap(e,this.options.tap),this.options.click&&m.click(e),void this._execEvent("scrollCancel")
if(this._events.flick&&a<200&&o<100&&l<100)this._execEvent("flick")
else{if(this.options.momentum&&a<300&&(t=this.hasHorizontalScroll?m.momentum(this.x,this.startX,a,this.maxScrollX,this.options.bounce?this.wrapperWidth:0,this.options.deceleration):{destination:r,duration:0},n=this.hasVerticalScroll?m.momentum(this.y,this.startY,a,this.maxScrollY,this.options.bounce?this.wrapperHeight:0,this.options.deceleration):{destination:i,duration:0},r=t.destination,i=n.destination,s=f.max(t.duration,n.duration),this.isInTransition=1),this.options.snap){var u=this._nearestSnap(r,i)
this.currentPage=u,s=this.options.snapSpeed||f.max(f.max(f.min(f.abs(r-u.x),1e3),f.min(f.abs(i-u.y),1e3)),300),r=u.x,i=u.y,this.directionX=0,this.directionY=0,c=this.options.bounceEasing}if(r!=this.x||i!=this.y)return(0<r||r<this.maxScrollX||0<i||i<this.maxScrollY)&&(c=m.ease.quadratic),void this.scrollTo(r,i,s,c)
this._execEvent("scrollEnd")}}}},_resize:function(){var e=this
clearTimeout(this.resizeTimeout),this.resizeTimeout=setTimeout(function(){e.refresh()},this.options.resizePolling)},resetPosition:function(e){var t=this.x,n=this.y
return e=e||0,!this.hasHorizontalScroll||0<this.x?t=0:this.x<this.maxScrollX&&(t=this.maxScrollX),!this.hasVerticalScroll||0<this.y?n=0:this.y<this.maxScrollY&&(n=this.maxScrollY),(t!=this.x||n!=this.y)&&(this.scrollTo(t,n,e,this.options.bounceEasing),!0)},disable:function(){this.enabled=!1},enable:function(){this.enabled=!0},refresh:function(){m.getRect(this.wrapper),this.wrapperWidth=this.wrapper.clientWidth,this.wrapperHeight=this.wrapper.clientHeight
var e=m.getRect(this.scroller)
this.scrollerWidth=e.width,this.scrollerHeight=e.height,this.maxScrollX=this.wrapperWidth-this.scrollerWidth,this.maxScrollY=this.wrapperHeight-this.scrollerHeight,this.hasHorizontalScroll=this.options.scrollX&&this.maxScrollX<0,this.hasVerticalScroll=this.options.scrollY&&this.maxScrollY<0,this.hasHorizontalScroll||(this.maxScrollX=0,this.scrollerWidth=this.wrapperWidth),this.hasVerticalScroll||(this.maxScrollY=0,this.scrollerHeight=this.wrapperHeight),this.endTime=0,this.directionX=0,this.directionY=0,
m.hasPointer&&!this.options.disablePointer&&(this.wrapper.style[m.style.touchAction]=m.getTouchAction(this.options.eventPassthrough,!0),this.wrapper.style[m.style.touchAction]||(this.wrapper.style[m.style.touchAction]=m.getTouchAction(this.options.eventPassthrough,!1))),this.wrapperOffset=m.offset(this.wrapper),this._execEvent("refresh"),this.resetPosition()},on:function(e,t){this._events[e]||(this._events[e]=[]),this._events[e].push(t)},off:function(e,t){if(this._events[e]){var n=this._events[e].indexOf(t)
;-1<n&&this._events[e].splice(n,1)}},_execEvent:function(e){if(this._events[e]){var t=0,n=this._events[e].length
if(n)for(;t<n;t++)this._events[e][t].apply(this,[].slice.call(arguments,1))}},scrollBy:function(e,t,n,a){e=this.x+e,t=this.y+t,n=n||0,this.scrollTo(e,t,n,a)},scrollTo:function(e,t,n,a){a=a||m.ease.circular,this.isInTransition=this.options.useTransition&&0<n
var r=this.options.useTransition&&a.style
!n||r?(r&&(this._transitionTimingFunction(a.style),this._transitionTime(n)),this._translate(e,t)):this._animate(e,t,n,a.fn)},scrollToElement:function(e,t,n,a,r){if(e=e.nodeType?e:this.scroller.querySelector(e)){var i=m.offset(e)
i.left-=this.wrapperOffset.left,i.top-=this.wrapperOffset.top
var o=m.getRect(e),l=m.getRect(this.wrapper)
!0===n&&(n=f.round(o.width/2-l.width/2)),!0===a&&(a=f.round(o.height/2-l.height/2)),i.left-=n||0,i.top-=a||0,i.left=0<i.left?0:i.left<this.maxScrollX?this.maxScrollX:i.left,i.top=0<i.top?0:i.top<this.maxScrollY?this.maxScrollY:i.top,t=null==t||"auto"===t?f.max(f.abs(this.x-i.left),f.abs(this.y-i.top)):t,this.scrollTo(i.left,i.top,t,r)}},_transitionTime:function(e){if(this.options.useTransition){e=e||0
var t=m.style.transitionDuration
if(t){if(this.scrollerStyle[t]=e+"ms",!e&&m.isBadAndroid){this.scrollerStyle[t]="0.0001ms"
var n=this
h(function(){"0.0001ms"===n.scrollerStyle[t]&&(n.scrollerStyle[t]="0s")})}if(this.indicators)for(var a=this.indicators.length;a--;)this.indicators[a].transitionTime(e)}}},_transitionTimingFunction:function(e){if(this.scrollerStyle[m.style.transitionTimingFunction]=e,this.indicators)for(var t=this.indicators.length;t--;)this.indicators[t].transitionTimingFunction(e)},_translate:function(e,t){if(this.options.useTransform?this.scrollerStyle[m.style.transform]="translate("+e+"px,"+t+"px)"+this.translateZ:(
e=f.round(e),t=f.round(t),this.scrollerStyle.left=e+"px",this.scrollerStyle.top=t+"px"),this.x=e,this.y=t,this.indicators)for(var n=this.indicators.length;n--;)this.indicators[n].updatePosition()},_initEvents:function(e){var t=e?m.removeEvent:m.addEvent,n=this.options.bindToWrapper?this.wrapper:i
t(i,"orientationchange",this),t(i,"resize",this),this.options.click&&t(this.wrapper,"click",this,!0),this.options.disableMouse||(t(this.wrapper,"mousedown",this),t(n,"mousemove",this),t(n,"mousecancel",this),t(n,"mouseup",this)),m.hasPointer&&!this.options.disablePointer&&(t(this.wrapper,m.prefixPointerEvent("pointerdown"),this),t(n,m.prefixPointerEvent("pointermove"),this),t(n,m.prefixPointerEvent("pointercancel"),this),t(n,m.prefixPointerEvent("pointerup"),this)),m.hasTouch&&!this.options.disableTouch&&(
t(this.wrapper,"touchstart",this),t(n,"touchmove",this),t(n,"touchcancel",this),t(n,"touchend",this)),t(this.scroller,"transitionend",this),t(this.scroller,"webkitTransitionEnd",this),t(this.scroller,"oTransitionEnd",this),t(this.scroller,"MSTransitionEnd",this)},getComputedPosition:function(){var e,t,n=i.getComputedStyle(this.scroller,null)
return t=this.options.useTransform?(e=+((n=n[m.style.transform].split(")")[0].split(", "))[12]||n[4]),+(n[13]||n[5])):(e=+n.left.replace(/[^-\d.]/g,""),+n.top.replace(/[^-\d.]/g,"")),{x:e,y:t}},_initIndicators:function(){var e,t=this.options.interactiveScrollbars,n="string"!=typeof this.options.scrollbars,a=[],r=this
this.indicators=[],this.options.scrollbars&&(this.options.scrollY&&(e={el:l("v",t,this.options.scrollbars),interactive:t,defaultScrollbars:!0,customStyle:n,resize:this.options.resizeScrollbars,shrink:this.options.shrinkScrollbars,fade:this.options.fadeScrollbars,listenX:!1},this.wrapper.appendChild(e.el),a.push(e)),this.options.scrollX&&(e={el:l("h",t,this.options.scrollbars),interactive:t,defaultScrollbars:!0,customStyle:n,resize:this.options.resizeScrollbars,shrink:this.options.shrinkScrollbars,
fade:this.options.fadeScrollbars,listenY:!1},this.wrapper.appendChild(e.el),a.push(e))),this.options.indicators&&(a=a.concat(this.options.indicators))
for(var i=a.length;i--;)this.indicators.push(new s(this,a[i]))
function o(e){if(r.indicators)for(var t=r.indicators.length;t--;)e.call(r.indicators[t])}this.options.fadeScrollbars&&(this.on("scrollEnd",function(){o(function(){this.fade()})}),this.on("scrollCancel",function(){o(function(){this.fade()})}),this.on("scrollStart",function(){o(function(){this.fade(1)})}),this.on("beforeScrollStart",function(){o(function(){this.fade(1,!0)})})),this.on("refresh",function(){o(function(){this.refresh()})}),this.on("destroy",function(){o(function(){this.destroy()}),
delete this.indicators})},_initWheel:function(){m.addEvent(this.wrapper,"wheel",this),m.addEvent(this.wrapper,"mousewheel",this),m.addEvent(this.wrapper,"DOMMouseScroll",this),this.on("destroy",function(){clearTimeout(this.wheelTimeout),this.wheelTimeout=null,m.removeEvent(this.wrapper,"wheel",this),m.removeEvent(this.wrapper,"mousewheel",this),m.removeEvent(this.wrapper,"DOMMouseScroll",this)})},_wheel:function(e){if(this.enabled){e.preventDefault()
var t,n,a,r,i=this
if(void 0===this.wheelTimeout&&i._execEvent("scrollStart"),clearTimeout(this.wheelTimeout),this.wheelTimeout=setTimeout(function(){i.options.snap||i._execEvent("scrollEnd"),i.wheelTimeout=void 0},400),"deltaX"in e)n=1===e.deltaMode?(t=-e.deltaX*this.options.mouseWheelSpeed,-e.deltaY*this.options.mouseWheelSpeed):(t=-e.deltaX,-e.deltaY)
else if("wheelDeltaX"in e)t=e.wheelDeltaX/120*this.options.mouseWheelSpeed,n=e.wheelDeltaY/120*this.options.mouseWheelSpeed
else if("wheelDelta"in e)t=n=e.wheelDelta/120*this.options.mouseWheelSpeed
else{if(!("detail"in e))return
t=n=-e.detail/3*this.options.mouseWheelSpeed}if(t*=this.options.invertWheelDirection,n*=this.options.invertWheelDirection,this.hasVerticalScroll||(t=n,n=0),this.options.snap)return a=this.currentPage.pageX,r=this.currentPage.pageY,0<t?a--:t<0&&a++,0<n?r--:n<0&&r++,void this.goToPage(a,r)
a=this.x+f.round(this.hasHorizontalScroll?t:0),r=this.y+f.round(this.hasVerticalScroll?n:0),this.directionX=0<t?-1:t<0?1:0,this.directionY=0<n?-1:n<0?1:0,0<a?a=0:a<this.maxScrollX&&(a=this.maxScrollX),0<r?r=0:r<this.maxScrollY&&(r=this.maxScrollY),this.scrollTo(a,r,0),1<this.options.probeType&&this._execEvent("scroll")}},_initSnap:function(){this.currentPage={},"string"==typeof this.options.snap&&(this.options.snap=this.scroller.querySelectorAll(this.options.snap)),this.on("refresh",function(){var e,t,n,a,r
,i,o,l=0,s=0,c=0,u=this.options.snapStepX||this.wrapperWidth,d=this.options.snapStepY||this.wrapperHeight
if(this.pages=[],this.wrapperWidth&&this.wrapperHeight&&this.scrollerWidth&&this.scrollerHeight){if(!0===this.options.snap)for(n=f.round(u/2),a=f.round(d/2);c>-this.scrollerWidth;){for(this.pages[l]=[],r=e=0;r>-this.scrollerHeight;)this.pages[l][e]={x:f.max(c,this.maxScrollX),y:f.max(r,this.maxScrollY),width:u,height:d,cx:c-n,cy:r-a},r-=d,e++
c-=u,l++}else for(e=(i=this.options.snap).length,t=-1;l<e;l++)o=m.getRect(i[l]),(0===l||o.left<=m.getRect(i[l-1]).left)&&(s=0,t++),this.pages[s]||(this.pages[s]=[]),c=f.max(-o.left,this.maxScrollX),r=f.max(-o.top,this.maxScrollY),n=c-f.round(o.width/2),a=r-f.round(o.height/2),this.pages[s][t]={x:c,y:r,width:o.width,height:o.height,cx:n,cy:a},c>this.maxScrollX&&s++
this.goToPage(this.currentPage.pageX||0,this.currentPage.pageY||0,0),this.options.snapThreshold%1==0?(this.snapThresholdX=this.options.snapThreshold,this.snapThresholdY=this.options.snapThreshold):(this.snapThresholdX=f.round(this.pages[this.currentPage.pageX][this.currentPage.pageY].width*this.options.snapThreshold),this.snapThresholdY=f.round(this.pages[this.currentPage.pageX][this.currentPage.pageY].height*this.options.snapThreshold))}}),this.on("flick",function(){var e=this.options.snapSpeed||f.max(
f.max(f.min(f.abs(this.x-this.startX),1e3),f.min(f.abs(this.y-this.startY),1e3)),300)
this.goToPage(this.currentPage.pageX+this.directionX,this.currentPage.pageY+this.directionY,e)})},_nearestSnap:function(e,t){if(!this.pages.length)return{x:0,y:0,pageX:0,pageY:0}
var n=0,a=this.pages.length,r=0
if(f.abs(e-this.absStartX)<this.snapThresholdX&&f.abs(t-this.absStartY)<this.snapThresholdY)return this.currentPage
for(0<e?e=0:e<this.maxScrollX&&(e=this.maxScrollX),0<t?t=0:t<this.maxScrollY&&(t=this.maxScrollY);n<a;n++)if(e>=this.pages[n][0].cx){e=this.pages[n][0].x
break}for(a=this.pages[n].length;r<a;r++)if(t>=this.pages[0][r].cy){t=this.pages[0][r].y
break}return n==this.currentPage.pageX&&((n+=this.directionX)<0?n=0:n>=this.pages.length&&(n=this.pages.length-1),e=this.pages[n][0].x),r==this.currentPage.pageY&&((r+=this.directionY)<0?r=0:r>=this.pages[0].length&&(r=this.pages[0].length-1),t=this.pages[0][r].y),{x:e,y:t,pageX:n,pageY:r}},goToPage:function(e,t,n,a){a=a||this.options.bounceEasing,e>=this.pages.length?e=this.pages.length-1:e<0&&(e=0),t>=this.pages[e].length?t=this.pages[e].length-1:t<0&&(t=0)
var r=this.pages[e][t].x,i=this.pages[e][t].y
n=void 0===n?this.options.snapSpeed||f.max(f.max(f.min(f.abs(r-this.x),1e3),f.min(f.abs(i-this.y),1e3)),300):n,this.currentPage={x:r,y:i,pageX:e,pageY:t},this.scrollTo(r,i,n,a)},next:function(e,t){var n=this.currentPage.pageX,a=this.currentPage.pageY;++n>=this.pages.length&&this.hasVerticalScroll&&(n=0,a++),this.goToPage(n,a,e,t)},prev:function(e,t){var n=this.currentPage.pageX,a=this.currentPage.pageY;--n<0&&this.hasVerticalScroll&&(n=0,a--),this.goToPage(n,a,e,t)},_initKeys:function(e){var t,n={pageUp:33,
pageDown:34,end:35,home:36,left:37,up:38,right:39,down:40}
if("object"==(0,c.default)(this.options.keyBindings))for(t in this.options.keyBindings)"string"==typeof this.options.keyBindings[t]&&(this.options.keyBindings[t]=this.options.keyBindings[t].toUpperCase().charCodeAt(0))
else this.options.keyBindings={}
for(t in n)this.options.keyBindings[t]=this.options.keyBindings[t]||n[t]
m.addEvent(i,"keydown",this),this.on("destroy",function(){m.removeEvent(i,"keydown",this)})},_key:function(e){if(this.enabled){var t,n=this.options.snap,a=n?this.currentPage.pageX:this.x,r=n?this.currentPage.pageY:this.y,i=m.getTime(),o=this.keyTime||0
switch(this.options.useTransition&&this.isInTransition&&(t=this.getComputedPosition(),this._translate(f.round(t.x),f.round(t.y)),this.isInTransition=!1),this.keyAcceleration=i-o<200?f.min(this.keyAcceleration+.25,50):0,e.keyCode){case this.options.keyBindings.pageUp:this.hasHorizontalScroll&&!this.hasVerticalScroll?a+=n?1:this.wrapperWidth:r+=n?1:this.wrapperHeight
break
case this.options.keyBindings.pageDown:this.hasHorizontalScroll&&!this.hasVerticalScroll?a-=n?1:this.wrapperWidth:r-=n?1:this.wrapperHeight
break
case this.options.keyBindings.end:a=n?this.pages.length-1:this.maxScrollX,r=n?this.pages[0].length-1:this.maxScrollY
break
case this.options.keyBindings.home:r=a=0
break
case this.options.keyBindings.left:a+=n?-1:5+this.keyAcceleration>>0
break
case this.options.keyBindings.up:r+=n?1:5+this.keyAcceleration>>0
break
case this.options.keyBindings.right:a-=n?-1:5+this.keyAcceleration>>0
break
case this.options.keyBindings.down:r-=n?1:5+this.keyAcceleration>>0
break
default:return}n?this.goToPage(a,r):(0<a?(a=0,this.keyAcceleration=0):a<this.maxScrollX&&(a=this.maxScrollX,this.keyAcceleration=0),0<r?(r=0,this.keyAcceleration=0):r<this.maxScrollY&&(r=this.maxScrollY,this.keyAcceleration=0),this.scrollTo(a,r,0),this.keyTime=i)}},_animate:function(i,o,l,s){var c=this,u=this.x,d=this.y,f=m.getTime(),p=f+l
this.isAnimating=!0,function e(){var t,n,a,r=m.getTime()
if(p<=r)return c.isAnimating=!1,c._translate(i,o),void(c.resetPosition(c.options.bounceTime)||c._execEvent("scrollEnd"))
a=s(r=(r-f)/l),t=(i-u)*a+u,n=(o-d)*a+d,c._translate(t,n),c.isAnimating&&h(e),3==c.options.probeType&&c._execEvent("scroll")}()},handleEvent:function(e){switch(e.type){case"touchstart":case"pointerdown":case"MSPointerDown":case"mousedown":this._start(e)
break
case"touchmove":case"pointermove":case"MSPointerMove":case"mousemove":this._move(e)
break
case"touchend":case"pointerup":case"MSPointerUp":case"mouseup":case"touchcancel":case"pointercancel":case"MSPointerCancel":case"mousecancel":this._end(e)
break
case"orientationchange":case"resize":this._resize()
break
case"transitionend":case"webkitTransitionEnd":case"oTransitionEnd":case"MSTransitionEnd":this._transitionEnd(e)
break
case"wheel":case"DOMMouseScroll":case"mousewheel":this._wheel(e)
break
case"keydown":this._key(e)
break
case"click":this.enabled&&!e._constructed&&(e.preventDefault(),e.stopPropagation())}}},s.prototype={handleEvent:function(e){switch(e.type){case"touchstart":case"pointerdown":case"MSPointerDown":case"mousedown":this._start(e)
break
case"touchmove":case"pointermove":case"MSPointerMove":case"mousemove":this._move(e)
break
case"touchend":case"pointerup":case"MSPointerUp":case"mouseup":case"touchcancel":case"pointercancel":case"MSPointerCancel":case"mousecancel":this._end(e)}},destroy:function(){this.options.fadeScrollbars&&(clearTimeout(this.fadeTimeout),this.fadeTimeout=null),this.options.interactive&&(m.removeEvent(this.indicator,"touchstart",this),m.removeEvent(this.indicator,m.prefixPointerEvent("pointerdown"),this),m.removeEvent(this.indicator,"mousedown",this),m.removeEvent(i,"touchmove",this),m.removeEvent(i,
m.prefixPointerEvent("pointermove"),this),m.removeEvent(i,"mousemove",this),m.removeEvent(i,"touchend",this),m.removeEvent(i,m.prefixPointerEvent("pointerup"),this),m.removeEvent(i,"mouseup",this)),this.options.defaultScrollbars&&this.wrapper.parentNode&&this.wrapper.parentNode.removeChild(this.wrapper)},_start:function(e){var t=e.touches?e.touches[0]:e
e.preventDefault(),e.stopPropagation(),this.transitionTime(),this.initiated=!0,this.moved=!1,this.lastPointX=t.pageX,this.lastPointY=t.pageY,this.startTime=m.getTime(),this.options.disableTouch||m.addEvent(i,"touchmove",this),this.options.disablePointer||m.addEvent(i,m.prefixPointerEvent("pointermove"),this),this.options.disableMouse||m.addEvent(i,"mousemove",this),this.scroller._execEvent("beforeScrollStart")},_move:function(e){var t,n,a,r,i=e.touches?e.touches[0]:e,o=m.getTime()
this.moved||this.scroller._execEvent("scrollStart"),this.moved=!0,t=i.pageX-this.lastPointX,this.lastPointX=i.pageX,n=i.pageY-this.lastPointY,this.lastPointY=i.pageY,a=this.x+t,r=this.y+n,this._pos(a,r),1==this.scroller.options.probeType&&300<o-this.startTime?(this.startTime=o,this.scroller._execEvent("scroll")):1<this.scroller.options.probeType&&this.scroller._execEvent("scroll"),e.preventDefault(),e.stopPropagation()},_end:function(e){if(this.initiated){if(this.initiated=!1,e.preventDefault(),
e.stopPropagation(),m.removeEvent(i,"touchmove",this),m.removeEvent(i,m.prefixPointerEvent("pointermove"),this),m.removeEvent(i,"mousemove",this),this.scroller.options.snap){var t=this.scroller._nearestSnap(this.scroller.x,this.scroller.y),n=this.options.snapSpeed||f.max(f.max(f.min(f.abs(this.scroller.x-t.x),1e3),f.min(f.abs(this.scroller.y-t.y),1e3)),300)
this.scroller.x==t.x&&this.scroller.y==t.y||(this.scroller.directionX=0,this.scroller.directionY=0,this.scroller.currentPage=t,this.scroller.scrollTo(t.x,t.y,n,this.scroller.options.bounceEasing))}this.moved&&this.scroller._execEvent("scrollEnd")}},transitionTime:function(e){e=e||0
var t=m.style.transitionDuration
if(t&&(this.indicatorStyle[t]=e+"ms",!e&&m.isBadAndroid)){this.indicatorStyle[t]="0.0001ms"
var n=this
h(function(){"0.0001ms"===n.indicatorStyle[t]&&(n.indicatorStyle[t]="0s")})}},transitionTimingFunction:function(e){this.indicatorStyle[m.style.transitionTimingFunction]=e},refresh:function(){this.transitionTime(),
this.options.listenX&&!this.options.listenY?this.indicatorStyle.display=this.scroller.hasHorizontalScroll?"block":"none":this.options.listenY&&!this.options.listenX?this.indicatorStyle.display=this.scroller.hasVerticalScroll?"block":"none":this.indicatorStyle.display=this.scroller.hasHorizontalScroll||this.scroller.hasVerticalScroll?"block":"none",this.scroller.hasHorizontalScroll&&this.scroller.hasVerticalScroll?(m.addClass(this.wrapper,"iScrollBothScrollbars"),m.removeClass(this.wrapper,
"iScrollLoneScrollbar"),this.options.defaultScrollbars&&this.options.customStyle&&(this.options.listenX?this.wrapper.style.right="8px":this.wrapper.style.bottom="8px")):(m.removeClass(this.wrapper,"iScrollBothScrollbars"),m.addClass(this.wrapper,"iScrollLoneScrollbar"),this.options.defaultScrollbars&&this.options.customStyle&&(this.options.listenX?this.wrapper.style.right="2px":this.wrapper.style.bottom="2px")),m.getRect(this.wrapper),this.options.listenX&&(this.wrapperWidth=this.wrapper.clientWidth,
this.options.resize?(this.indicatorWidth=f.max(f.round(this.wrapperWidth*this.wrapperWidth/(this.scroller.scrollerWidth||this.wrapperWidth||1)),8),this.indicatorStyle.width=this.indicatorWidth+"px"):this.indicatorWidth=this.indicator.clientWidth,this.maxPosX=this.wrapperWidth-this.indicatorWidth,"clip"==this.options.shrink?(this.minBoundaryX=8-this.indicatorWidth,this.maxBoundaryX=this.wrapperWidth-8):(this.minBoundaryX=0,this.maxBoundaryX=this.maxPosX),
this.sizeRatioX=this.options.speedRatioX||this.scroller.maxScrollX&&this.maxPosX/this.scroller.maxScrollX),this.options.listenY&&(this.wrapperHeight=this.wrapper.clientHeight,this.options.resize?(this.indicatorHeight=f.max(f.round(this.wrapperHeight*this.wrapperHeight/(this.scroller.scrollerHeight||this.wrapperHeight||1)),8),this.indicatorStyle.height=this.indicatorHeight+"px"):this.indicatorHeight=this.indicator.clientHeight,this.maxPosY=this.wrapperHeight-this.indicatorHeight,"clip"==this.options.shrink?(
this.minBoundaryY=8-this.indicatorHeight,this.maxBoundaryY=this.wrapperHeight-8):(this.minBoundaryY=0,this.maxBoundaryY=this.maxPosY),this.maxPosY=this.wrapperHeight-this.indicatorHeight,this.sizeRatioY=this.options.speedRatioY||this.scroller.maxScrollY&&this.maxPosY/this.scroller.maxScrollY),this.updatePosition()},updatePosition:function(){var e=this.options.listenX&&f.round(this.sizeRatioX*this.scroller.x)||0,t=this.options.listenY&&f.round(this.sizeRatioY*this.scroller.y)||0
this.options.ignoreBoundaries||(e<this.minBoundaryX?("scale"==this.options.shrink&&(this.width=f.max(this.indicatorWidth+e,8),this.indicatorStyle.width=this.width+"px"),e=this.minBoundaryX):e>this.maxBoundaryX?e="scale"==this.options.shrink?(this.width=f.max(this.indicatorWidth-(e-this.maxPosX),8),this.indicatorStyle.width=this.width+"px",this.maxPosX+this.indicatorWidth-this.width):this.maxBoundaryX:"scale"==this.options.shrink&&this.width!=this.indicatorWidth&&(this.width=this.indicatorWidth,
this.indicatorStyle.width=this.width+"px"),t<this.minBoundaryY?("scale"==this.options.shrink&&(this.height=f.max(this.indicatorHeight+3*t,8),this.indicatorStyle.height=this.height+"px"),t=this.minBoundaryY):t>this.maxBoundaryY?t="scale"==this.options.shrink?(this.height=f.max(this.indicatorHeight-3*(t-this.maxPosY),8),this.indicatorStyle.height=this.height+"px",this.maxPosY+this.indicatorHeight-this.height):this.maxBoundaryY:"scale"==this.options.shrink&&this.height!=this.indicatorHeight&&(
this.height=this.indicatorHeight,this.indicatorStyle.height=this.height+"px")),this.x=e,this.y=t,this.scroller.options.useTransform?this.indicatorStyle[m.style.transform]="translate("+e+"px,"+t+"px)"+this.scroller.translateZ:(this.indicatorStyle.left=e+"px",this.indicatorStyle.top=t+"px")},_pos:function(e,t){e<0?e=0:e>this.maxPosX&&(e=this.maxPosX),t<0?t=0:t>this.maxPosY&&(t=this.maxPosY),e=this.options.listenX?f.round(e/this.sizeRatioX):this.scroller.x,t=this.options.listenY?f.round(t/this.sizeRatioY
):this.scroller.y,this.scroller.scrollTo(e,t)},fade:function(e,t){if(!t||this.visible){clearTimeout(this.fadeTimeout),this.fadeTimeout=null
var n=e?250:500,a=e?0:300
e=e?"1":"0",this.wrapperStyle[m.style.transitionDuration]=n+"ms",this.fadeTimeout=setTimeout(function(e){this.wrapperStyle.opacity=e,this.visible=+e}.bind(this,e),a)}}},e.utils=m,i.IScroll=e}(window,document,Math)},FYsW:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:o,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"runner:generate:widgets-query-map":return(0,r.default)({},e,{widgetQueryMap:(0,i.getScreenWidgetsMap)(Widget.irecords)})
case"runner:update:state":return(0,r.default)({},e,a)
case"runner:reset:state":return o
default:return e}}
var r=a(n("MVZn")),i=n("IB8Z"),o={widgetQueryMap:{},activeCid:"",transition:{name:"slideleft",delay:0,duration:2e3,offset:100,callback:function(){}},history:[],screenInfoMap:{}}},FkXu:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.getFontWeightStrDepandOnBoldType=t.getFontWeightNumDepandOnBoldType=t.getFontWeightStr=t.getFontFamilyAndWeightText=t.getTypeWeightList=t.WESTERN_COMMON_FONT_FAMILY_LIST=t.HOSTED_COMMON_FONT_FAMILY_LIST=t.HOSTED_COMMERCIAL_FANGZHENG_FONT_FAMILY_LIST=void 0
var r=a(n("RIqP")),i=a(n("yl0K")),o=i.default.HOSTED_COMMERCIAL_FANGZHENG_LIST,l=i.default.HOSTED_COMMON_LIST,s=i.default.WESTERN_COMMON_LIST,c=[].concat((0,r.default)(o),(0,r.default)(l),(0,r.default)(s)),u=function(e){return{label:e.label,value:e.family,limitedDevices:e.limitedDevices}},d=o.map(u)
t.HOSTED_COMMERCIAL_FANGZHENG_FONT_FAMILY_LIST=d
var f=l.map(u)
t.HOSTED_COMMON_FONT_FAMILY_LIST=f
var p=s.map(u)
t.WESTERN_COMMON_FONT_FAMILY_LIST=p
var h={regular:400,light:300,bold:700},m={regular:I18N.rich_text_settings.weight.regular,light:I18N.rich_text_settings.weight.light,bold:I18N.rich_text_settings.weight.bold}
t.getTypeWeightList=function(t){var e=c.find(function(e){return e.family===t})
return e?e.typeList.map(function(e){return{label:m[e],value:e}}):[]}
t.getFontFamilyAndWeightText=function(t,e){var n=o.find(function(e){return e.family===t})
return n?"".concat(n.label,"-").concat(m[e]):"".concat(t,"-").concat(e)}
var v=function(t){return h[t]?t:Object.keys(h).find(function(e){return String(h[e])===String(t)})||"regular"}
t.getFontWeightStr=v
t.getFontWeightNumDepandOnBoldType=function(e,t){var n=h[e]
return Number(t)?700:n}
t.getFontWeightStrDepandOnBoldType=function(e,t,n){var a=v(e)
return Number(n)?t:a}},G916:function(e,t,n){e.exports={nav:"Hiz6yu3fLMLU-8yBEpNTi","nav-item":"_10LJDTQtIaisEickywA9Y6"}},GWLA:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("MVZn")),o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=r(n("17x9")),h=a(n("q1tI")),m=n("6XO9"),v=n("wYtL"),g=(r(n("JSCU")),n("h0FN")),y=r(n("zy85")),b=r(n("UbMB")).default.bind(y.default),S={type:0,name:"自定义链接",target_cid:"screen-cid-1",transition:{name:"slide-left",duration:2e3}},w=[{value:1,label:"screen-link"},{value:2,label:"state-link"},{value:3,label:"panel-link"},{value:4,label:"widget-link"}],E=Link.TYPE,k=E.screen_link,
C=E.state_link,x=E.panel_link,T=E.widget_link,_=function(e){function n(){var t
return(0,o.default)(this,n),t=(0,s.default)(this,(0,c.default)(n).call(this)),(0,f.default)((0,u.default)(t),"handleLinkType",function(e){t.updateLinkAttr({type:Number(e)})}),(0,f.default)((0,u.default)(t),"handleLinkTarget",function(e){return t.updateLinkAttr({targetCid:e})}),(0,f.default)((0,u.default)(t),"updateLinkAttr",function(e){t.setState({currentLink:(0,i.default)({},t.state.currentLink,e)})}),(0,f.default)((0,u.default)(t),"handleSubmit",function(){var e=t.state.currentLink
t.props.dispatch,console.log(e)}),t.state={currentLink:S},t}return(0,d.default)(n,e),(0,l.default)(n,[{key:"render",value:function(){var e=this.state.currentLink
return h.default.createElement("div",{className:b("runner-control-panel")},h.default.createElement("div",{className:"line"},h.default.createElement("span",null,"链接类型"),h.default.createElement(v.Select,{value:e.type,optionList:w,onChange:this.handleLinkType})),M(e),h.default.createElement("button",{className:"submit",onClick:this.handleSubmit},"执行"))}}]),n}(h.PureComponent)
t.default=_,(0,f.default)(_,"propTypes",{dispatch:p.default.func})
var M=function(e){switch(e.type){case k:return h.default.createElement(P,{link:e})
case C:return h.default.createElement(I,{link:e})
case x:return h.default.createElement(N,{link:e})
case T:return h.default.createElement(R,{link:e})
default:return null}},P=function(e){function t(){return(0,o.default)(this,t),(0,s.default)(this,(0,c.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,l.default)(t,[{key:"render",value:function(){var e=this.props.link,t=[]
return MB.currentProject.cscreens().forEach(function(e){e.cid!==MB.currentScreen.cid&&t.push({value:e.cid,label:e.name})}),h.default.createElement(h.default.Fragment,null,h.default.createElement("div",{className:"line"},h.default.createElement("span",null,"目标页面"),h.default.createElement(v.Select,{value:e.targetCid,optionList:t,onChange:this.handleLinkTarget})),h.default.createElement("div",{className:"line"},h.default.createElement("span",null,"动画名称"),h.default.createElement(v.Select,{value:e.transition,
optionList:g.TRANSITIONS,onChange:this.handleLinkTarget})))}}]),t}(h.PureComponent),I=function(e){function t(){return(0,o.default)(this,t),(0,s.default)(this,(0,c.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,l.default)(t,[{key:"render",value:function(){var e=this.props.link,t=[{cid:"default",name:"默认状态"}]
return MB.currentScreen.cscreenstates().forEach(function(e){e.cid!==MB.currentScreen.state_cid&&t.push({value:e.cid,label:e.name})}),h.default.createElement(h.default.Fragment,null,h.default.createElement("div",{className:"line"},h.default.createElement("span",null,"目标状态"),h.default.createElement(v.Select,{value:e.targetCid,optionList:t,onChange:this.handleLinkTarget})),h.default.createElement("div",{className:"detail"},h.default.createElement("div",{className:"desc"},"神奇移动"),h.default.createElement(
m.Switch,{size:"small",isChecked:"none"===e.transition,onChange:this.handleLinkChange})))}}]),t}(h.PureComponent),N=function(e){function t(){return(0,o.default)(this,t),(0,s.default)(this,(0,c.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,l.default)(t,[{key:"render",value:function(){var e=this.props.link,t=MB.currentScreen.cpanels().map(function(e){return{value:e.cid,label:e.display_name}})
return h.default.createElement(h.default.Fragment,null,h.default.createElement("div",{className:"line"},h.default.createElement("span",null,"目标状态"),h.default.createElement(v.Select,{value:e.targetCid,optionList:t,onChange:this.handleLinkTarget})),h.default.createElement("div",{className:"detail"},h.default.createElement("div",{className:"desc"},"神奇移动"),h.default.createElement(m.Switch,{size:"small",isChecked:"none"===e.transition,onChange:this.handleLinkChange})))}}]),t}(h.PureComponent),R=function(e){
function t(){return(0,o.default)(this,t),(0,s.default)(this,(0,c.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,l.default)(t,[{key:"render",value:function(){var e=this.props.link,t=MB.currentScreen.cwidgets().map(function(e){return{value:e.cid,label:e.display_name}})
return h.default.createElement(h.default.Fragment,null,h.default.createElement("div",{className:"line"},h.default.createElement("span",null,"目标状态"),h.default.createElement(v.Select,{value:e.targetCid,optionList:t,onChange:this.handleLinkTarget})),h.default.createElement("div",{className:"detail"},h.default.createElement("div",{className:"desc"},"神奇移动"),h.default.createElement(m.Switch,{size:"small",isChecked:"none"===e.transition,onChange:this.handleLinkChange})))}}]),t}(h.PureComponent)},H27A:function(e,t,
n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var s=r(n("o0o1")),i=r(n("yXPU")),o=r(n("lwsE")),l=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("PJYZ")),f=r(n("7W2i")),p=r(n("lSNA")),m=a(n("q1tI")),h=r(n("17x9")),v=n("DqDi"),g=n("i6OX"),y=r(n("4QcC")),b=r(n("Ur7v")),S=r(n("lCKy")),w=r(n("iX79")),E=n("/5+U"),k=n("1iCU"),C=n("t3Un"),x=n("2EV6"),T=n("Gbs1"),_=n("6x+O"),M=n("/5+U"),P=r(n("rtgd")),I=r(n("UbMB")).default.bind(P.default),N=[{label:I18N.preview.preview,icon:m.default.createElement(g.SVGIcon,{name:"design/preview"})},{
label:I18N.preview_panel.developer_mode,icon:m.default.createElement(g.SVGIcon,{name:"design/inspect"})},{label:I18N.preview_panel.comment,icon:m.default.createElement(g.SVGIcon,{name:"design/comment"})}],R=N.slice(0,2),L=function(e){function i(){var e,a;(0,o.default)(this,i)
for(var t=arguments.length,n=new Array(t),r=0;r<t;r++)n[r]=arguments[r]
return a=(0,c.default)(this,(e=(0,u.default)(i)).call.apply(e,[this].concat(n))),(0,p.default)((0,d.default)(a),"setElementRef",function(e){return a.$elem=e}),(0,p.default)((0,d.default)(a),"handleTabChange",function(e){var t=a.props.dispatch,n=k.PREVIEW_CONFIG[e]
t({type:"entry:preview:select",payload:{toolbarActiveItem:k.PREVIEW_CONFIG[e]}}),MB.event("preview","".concat(k.TOOLBAR_TRAKING_CONFIG[n]))}),(0,p.default)((0,d.default)(a),"handTooltip",function(){$(a.$elem).tooltip({container:"body",selector:".project-name",placement:"right",trigger:"hover",title:function(e,t,n){var a=this.offsetWidth,r=this.scrollWidth,i=this.textContent
return a<r&&[i]}})}),a}return(0,f.default)(i,e),(0,l.default)(i,[{key:"componentDidMount",value:function(){this.handTooltip()}},{key:"UNSAFE_componentWillReceiveProps",value:function(e){var t=e.toolbarActiveItem,n=e.loadSliceUrl
t!=this.props.toolbarActiveItem&&this.props.dispatch({type:"reducer:preview-toolbar:update",payload:{isShowColorPicker:!1,isSelectLayer:!1}}),n!=this.props.loadSliceUrl&&A(n)}},{key:"render",value:function(){var e=this.props,t=e.scale,n=e.project,a=e.dispatch,r=e.toolbarActiveItem,i=e.isScrollable,o=e.isHighlight,l=e.isStickyShow,s=e.shellType,c=e.showToolBarText,u=k.PREVIEW_CONFIG.indexOf(r)||0,d=r!=k.PREVIEW,f=n.name||"",p=MB.isHTMLZip()?R:N,h=m.default.createElement(y.default,{scale:t,dispatch:a})
return"project"!==(0,x.getProjectType)(n)?h:m.default.createElement("header",{className:I("preview-toolbar",{"hide-text":!c})},m.default.createElement("div",{className:"toolbar-left",ref:this.setElementRef},(0,M.canBackToWorkspace)()&&m.default.createElement("a",{title:I18N.back,onClick:j,className:"back-icon"},m.default.createElement(g.SVGIcon,{name:"angle_bracket_left"})),m.default.createElement("span",{className:"project-name"},(0,_.getTextOfHTML)(f))),m.default.createElement("div",{
className:"toolbar-main"},h,m.default.createElement("div",{className:"toolbar-main-wrapper"},m.default.createElement(v.NavigationBar,{tabs:p,activeIndex:u,onChange:this.handleTabChange,className:"preview-toolbar-nav",hideBorder:!0}))),m.default.createElement("div",{className:"toolbar-right"},m.default.createElement(S.default,{canSetDeviceShell:(0,T.canSetDeviceShell)(n),disabled:d,isScrollable:i,isHighlight:o,isStickyShow:l,shellType:s,dispatch:a}),m.default.createElement("span",{className:"line"}),
m.default.createElement(b.default,{dispatch:a}),m.default.createElement("span",{className:"line"}),m.default.createElement(w.default,{dispatch:a})))}}]),i}(m.PureComponent)
t.default=L,(0,p.default)(L,"propTypes",{scale:h.default.number,project:h.default.object,toolbarActiveItem:h.default.string,loadSliceUrl:h.default.string,showToolBarText:h.default.bool,isScrollable:h.default.bool,isHighlight:h.default.bool,isStickyShow:h.default.bool,shellType:h.default.string,dispatch:h.default.func})
var j=function(){(0,M.canBackToWorkspace)()&&MB.designer.backDesign()},A=function(){var t=(0,i.default)(s.default.mark(function e(n){var a,r,i,o,l
return s.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:a=!0,i=1
case 2:if(a)return e.next=5,(0,E.setTimeoutAsync)(Math.min(2e3*i++,1e4))
e.next=16
break
case 5:return e.next=7,t=n,(0,C.requestJSON)(t,null,{method:"POST"})
case 7:if(o=e.sent,l=o.url,"ok"===o.status&&(a=!1,r=l),20<i)return(0,E.downloadFail)(),e.abrupt("return",!1)
e.next=14
break
case 14:e.next=2
break
case 16:return(0,E.downloadWithATag)({url:"/".concat(r),type:"zip"}),e.abrupt("return",!0)
case 18:case"end":return e.stop()}var t},e)}))
return function(e){return t.apply(this,arguments)}}()},HFhh:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var h=n("Czp5"),a=n("WVP6"),r={id:null,name:"",email:"",avatar:"",plan:{state:"",type:"free",rawType:"free",daysLeft:""}},i=(0,a.createStateStore)(r),o=i.getState,l=i.setState,s=i.wrapEntry
var c={entryMap:{"user:set":s(function(e,t,n){var a=t.dispatch,r=n.payload,i=void 0===r?{}:r,o=i.id,l=void 0===o?null:o,s=i.name,c=void 0===s?"":s,u=i.email,d=void 0===u?"":u,f=i.avatar,p=void 0===f?"":f
a({type:"reducer:user:update",payload:(0,h.objectMerge)(e,{id:l,name:c,email:d,avatar:p,plan:function(e){var t=e.plan,n=e.state,a=(e.limitation,e.days_left)
return{state:n||"",type:"active"===n&&t||"free",rawType:t||"free",daysLeft:a||""}}(i)})})}),"user:clear":s(function(e,t,n){(0,t.dispatch)({type:"reducer:user:update",payload:r})})},getState:o,setState:l}
t.default=c},HNPj:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=a(n("a1gu")),l=a(n("Nsbk")),s=a(n("7W2i")),c=a(n("q1tI")),u=a(n("17x9")),d=a(n("Y69h")),f=a(n("7Rdd")),p=a(n("0uCA")),h=a(n("mCdf")),m=n("ZXhj"),v=n("IdPL"),g=a(n("TjoA")),y=function(e){function t(){return(0,r.default)(this,t),(0,o.default)(this,(0,l.default)(t).apply(this,arguments))}return(0,s.default)(t,e),(0,i.default)(t,[{key:"shouldComponentUpdate",value:function(e){return!((0,m.checkSameRect)(e.baseRect,this.props.baseRect)&&(0,m.checkSameRect)(e.refRect,
this.props.refRect)&&(0,m.checkSameRect)(e.screen,this.props.screen)&&e.theme===this.props.theme)}},{key:"render",value:function(){var e=this.props,t=e.baseRect,n=e.refRect,a=e.screen,r=e.theme,i=e.renderValue,o=v.STYLE_MAP[r].verboseAuxiliaryLines
return c.default.createElement("div",{className:g.default["distance-measurement-container"]},c.default.createElement(d.default,{baseRect:t,refRect:n,screen:a,style:v.STYLE_MAP[r].distanceMarks,renderValue:i}),o?c.default.createElement(p.default,{refRect:n,screen:a,style:v.STYLE_MAP[r].auxiliaryLines}):c.default.createElement(h.default,{baseRect:t,refRect:n,screen:a,style:v.STYLE_MAP[r].auxiliaryLines}),c.default.createElement(f.default,{refRect:n,screen:a,style:v.STYLE_MAP[r].refRectBorder}))}}]),t}(
c.default.Component);(t.default=y).propTypes={baseRect:u.default.object,refRect:u.default.object,screen:u.default.object,theme:u.default.string,renderValue:u.default.func}},HfeQ:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),d=r(n("17x9")),w=a(n("q1tI")),E=n("6XO9")
n("wfO3")
var f=function(e){function t(){return(0,i.default)(this,t),(0,l.default)(this,(0,s.default)(t).apply(this,arguments))}return(0,c.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.dispatch,n=e.isOpen,a=e.type,r=e.alertType,i=e.title,o=e.desc,l=void 0===o?i:o,s=e.isHTML,c=e.onClose,u=void 0===c?function(){return t({type:"container:modal:close"})}:c,d=e.onCancel,f=void 0===d?function(){return null}:d,p=e.onConfirm,h=e.canClose,m=e.canCancel,v=e.canConfirm,g=e.cancelText,
y=e.confirmText,b=m?function(){f&&f(),u&&u()}:void 0,S=v?function(){p&&p(),u&&u()}:void 0
return w.default.createElement(E.Modal,{isOpen:n,type:a,portalClassName:"global-alert-portal",title:i!==l&&i?i:I18N.reminder,onClose:function(){"function"==typeof f&&f(),u()},canClose:h,onCancel:b,onConfirm:S,cancelText:g,confirmText:y},s?w.default.createElement("p",{className:"desc",dangerouslySetInnerHTML:{__html:l}}):w.default.createElement("div",{className:"desc"},l),"prompt"===r&&w.default.createElement(E.FormLabel,{name:I18N.password},w.default.createElement(E.Input,{type:"password",
className:"prompt-pwd"})))}}]),t}(w.PureComponent)
t.default=f,(0,u.default)(f,"propTypes",{dispatch:d.default.func,isOpen:d.default.bool,type:d.default.string,alertType:d.default.oneOf(["confirm","alert","prompt"]),onClose:d.default.func,onCancel:d.default.func,onConfirm:d.default.func,canClose:d.default.bool,canCancel:d.default.bool,canConfirm:d.default.bool,confirmText:d.default.string,cancelText:d.default.string,title:d.default.string,desc:d.default.any,isHTML:d.default.bool}),(0,u.default)(f,"defaultProps",{type:"alert"})},Hlt7:function(e,t,n){
"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.scrollParent=t.checkInvision=t.checkOverflowVisbile=t.filterSearch=void 0
var u=a(n("MVZn")),d=a(n("J4zp")),p=a(n("i8i4"))
t.filterSearch=function(e,t,n){for(var a=[],r=0,i=0,o=Object.entries(e);i<o.length;i++){var l=(0,d.default)(o[i],2),s=l[0],c=l[1]
t&&0<t.length&&c.toLowerCase().includes(t)&&a.push((0,u.default)({},n[s],{index:r++}))}return a}
var r=function(e){if(!e)return document.documentElement
for(var t="absolute"===e.style.position,n=/(scroll|auto)/,a=e;a;){if(!a.parentNode)return e.ownerDocument||document.documentElement
var r=window.getComputedStyle(a),i=r.position,o=r.overflow,l=r["overflow-x"],s=r["overflow-y"]
if("static"===i&&t&&(a=a.parentNode),n.test(o)&&n.test(l)&&n.test(s))return a
a=a.parentNode}return e.ownerDocument||e.documentElement||document.documentElement}
t.scrollParent=r
var h=0,m=0,i=function(e,t){var n,a,r=p.default.findDOMNode(e)
try{var i=t.getBoundingClientRect()
n=i.top,a=i.height}catch(e){n=h,a=m}var o,l,s=window.innerHeight||document.documentElement.clientHeight,c=Math.max(n,0),u=Math.min(s,n+a)-c
try{var d=r.getBoundingClientRect()
o=d.top,l=d.height}catch(e){o=h,l=m}var f=o-c
return f<=u&&0<=f+l}
t.checkOverflowVisbile=i
t.checkInvision=function(e){var t=p.default.findDOMNode(e),n=r(t)
return!!i(e,n)}},Hrzm:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=n("uavl"),m=n("zQyp")
n("dAiO")
var v=function(e){function i(){var e,r;(0,o.default)(this,i)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return r=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(n))),(0,f.default)((0,u.default)(r),"renderStickies",function(){var e=r.props,t=e.screenCid,n=e.stateCid
if(!t||!n)return null
var a=[]
return Widget.all().forEach(function(e){"sticky"===e.name&&e.screen_cid===t&&a.push(Widgetstate.find(n+e.cid)||e)}),a.map(function(e){return p.default.createElement(g,{key:e.cid,sticky:e})})}),r}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){return p.default.createElement("div",{id:"sticky-container",onClick:this.handleClick},p.default.createElement("div",{id:"stickies"},this.renderStickies()))}}]),i}(p.PureComponent)
t.default=v,(0,f.default)(v,"propTypes",{screenCid:i.default.string,stateCid:i.default.string})
var g=function(e){function i(){var e,n;(0,o.default)(this,i)
for(var t=arguments.length,a=new Array(t),r=0;r<t;r++)a[r]=arguments[r]
return n=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(n),"handleClick",function(e){var t=n.props.sticky
Link.find(t.link_cids)&&MB.runner.eventHandler.prepareJump(e,["tap","click"])}),n}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props.sticky,t=(0,m.getWidgetClassName)(e,"p"),n=(0,m.getWidgetStyle)(e,"p"),a=Link.find(e.link_cids)?e.link_cids:""
return p.default.createElement("div",{key:e.cid,"data-cid":e.cid,"data-link_cid":a,id:"widget".concat(e.cid,"p"),className:t,style:n,onClick:this.handleClick},(0,h.getWidgetContent)(e))}}]),i}(p.PureComponent);(0,f.default)(g,"propTypes",{sticky:i.default.object})},IV71:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),Object.defineProperty(t,"WebpackInterface",{enumerable:!0,get:function(){return r.default}}),Object.defineProperty(t,"mixConfig",{enumerable:!0,get:function(){return i.default}}),t.default=void 0
var r=a(n("jeLk")),i=a(n("JPxj")),o=r.default
t.default=o},Ibie:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.patchWidgetSize=void 0
t.patchWidgetSize=function(e,t){var n,a=2<arguments.length&&void 0!==arguments[2]?arguments[2]:20
switch(e.name){case"status_bar":n=0
break
case"keyboard":case"tab_bar":n=t.height-e.height
break
case"navigation_bar":n=a
break
default:n=e.top}return e.top=n,r(e.name)&&(e.width=t.width),e}
var r=function(e){return["status_bar","keyboard","tab_bar"].includes(e)}},IdPL:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0})
t.STYLE_MAP=void 0
t.STYLE_MAP={design:{distanceMarks:{showStartAndEndBoundary:!1,dashed:!1,colorForLines:"#eb5648",colorForText:"#eb5648"},refRectBorder:{dashed:!1,colorForLines:"#eb5648"},verboseAuxiliaryLines:!1,auxiliaryLines:{dashed:!0,colorForLines:"#eb5648"}},preview:{distanceMarks:{showStartAndEndBoundary:!0,dashed:!0,colorForLines:"#ff7100"},refRectBorder:{dashed:!0,colorForLines:"#1e98ea"},verboseAuxiliaryLines:!0,auxiliaryLines:{dashed:!0,colorForLines:"#1e98ea"}}}},J2m7:function(e,t,n){var a=n("XKAG")(n("UfWW"))
e.exports=a},JPxj:function(e,t,n){"use strict"
function a(e,t,n){return n?t?e(t,n):n:t}function r(e,t){var n={}
function a(e,t){n[e]=t}for(var r in e)a(r,e[r])
for(var i in t)a(i,t[i])
return n}function i(e,t){return function(){return e.apply(void 0,arguments),t.apply(void 0,arguments)}}Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(e){var t={containerReducerMap:{},viewMap:{},sagaMap:{},extendCallback:null}
return e.forEach(function(e){t.containerReducerMap=a(r,t.containerReducerMap,e.containerReducerMap),t.viewMap=a(r,t.viewMap,e.viewMap),t.extendCallback=a(i,t.extendCallback,e.extendCallback),t.sagaMap=a(r,t.sagaMap,e.sagaMap)}),t}},JSCU:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("TSYQ")),m=r(n("ctY3")),v=function(e){function n(e){var t
return(0,i.default)(this,n),t=(0,l.default)(this,(0,s.default)(n).call(this,e)),(0,d.default)((0,c.default)(t),"handleChange",function(e){return t.setState({value:e})}),(0,d.default)((0,c.default)(t),"handleBlur",function(){""===t.state.value&&t.setState({value:t.initialValue}),t.props.onConfirm(t.state.value)}),t.state={value:e.value},t.initialValue=e.value,t}return(0,u.default)(n,e),(0,o.default)(n,[{key:"render",value:function(){var e=this.props,t=e.isEditing,n=e.className,a=this.state.value
return p.default.createElement(m.default,{value:a,className:(0,h.default)("editable-span",n),editing:t,onBlur:this.handleBlur,onChange:this.handleChange})}}]),n}(p.PureComponent)
t.default=v,(0,d.default)(v,"propTypes",{value:f.default.string,className:f.default.string,isEditing:f.default.bool,onConfirm:f.default.func})},JXIg:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=(0,n("WVP6").createStateStore)({teamCid:null,projectCid:null,screenCid:null,userRole:"guest"}),r=a.getState,i=a.setState,o={"current:set":(0,a.wrapEntry)(function(e,t,n){var a=t.dispatch,r=n.payload,i=r.project,o=r.screen,l=r.userCollaborator
a({type:"reducer:current:update",payload:{teamCid:i&&i.team_cid||null,projectCid:i&&i.cid||null,screenCid:o&&o.cid||null,userRole:function(e){return s.has(e)?e:"guest"}(l&&l.role)}})})},s=new Set(["owner","admin","editor","viewer"])
var l={entryMap:o,getState:r,setState:i}
t.default=l},JfQ8:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.receiveResourceError=t.RECEIVE_RESOURCE_ERROR=t.receiveResourceSuccess=t.RECEIVE_RESOURCE_SUCCESS=t.SET_VISIBILITY_SCREEN=void 0
var i=a(n("MVZn"))
t.SET_VISIBILITY_SCREEN="SET_VISIBILITY_SCREEN"
var o="RECEIVE_RESOURCE_SUCCESS"
t.RECEIVE_RESOURCE_SUCCESS=o
t.receiveResourceSuccess=function(e,t){var n=t.document,a=t.layers,r=t.artboard
return{type:o,payload:(0,i.default)({screenID:e},n,{layers:a,artboard:r})}}
var r="RECEIVE_RESOURCE_ERROR"
t.RECEIVE_RESOURCE_ERROR=r
t.receiveResourceError=function(e,t){return{type:r,payload:{screenID:e,error:t}}}},K7IS:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=r(n("TSYQ")),m=r(n("4dyd")),v=r(n("mesP")),g=r(n("mMVB")),y=n("mC/1"),b=function(e){function i(){var e,a;(0,o.default)(this,i)
for(var t=arguments.length,n=new Array(t),r=0;r<t;r++)n[r]=arguments[r]
return a=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(n))),(0,f.default)((0,u.default)(a),"handleResize",function(){var e=document.querySelector("#preview_scrollBar_viewport").getBoundingClientRect(),t=e.width,n=e.height
a.props.dispatch({type:"preview:scrollbar:viewport",payload:{width:t,height:n}})}),(0,f.default)((0,u.default)(a),"handleBackToOrigin",function(){a.props.dispatch({type:"preview:set:canvas:offset",payload:{offset:{x:0,y:0}}})}),a}return(0,d.default)(i,e),(0,l.default)(i,[{key:"componentDidMount",value:function(){this.handleResize()}},{key:"render",value:function(){var e=this.props,t=e.isLayerActive,n=e.isDisplaced
return p.default.createElement(y.StyledMainContent,{id:"preview_scrollBar_viewport"},t&&p.default.createElement(v.default,null),p.default.createElement(y.StyledResetButton,{className:(0,h.default)({"is-show":n}),onClick:this.handleBackToOrigin},I18N.click_to_origin),p.default.createElement(g.default,null),p.default.createElement(m.default,{onResize:this.handleResize}))}}]),i}(p.PureComponent)
t.default=b,(0,f.default)(b,"propTypes",{isLayerActive:i.default.bool,isDisplaced:i.default.bool,dispatch:i.default.func})},KHYK:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=a(n("pVnL")),l=a(n("lwsE")),i=a(n("W8MJ")),s=a(n("a1gu")),c=a(n("Nsbk")),u=a(n("PJYZ")),d=a(n("7W2i")),f=a(n("lSNA")),r=a(n("MVZn")),p=a(n("J4zp")),h=a(n("17x9")),m=a(n("q1tI")),v=a(n("HNPj")),g=n("/5+U"),y=a(n("dZ9F")),b=function(e){var t=e.kind?0:e.rotation,n=(0,g.getMinBoundingRect)((0,r.default)({},e,{rotate:t})),a=(0,p.default)(n,4)
return{top:a[0],left:a[1],width:a[2],height:a[3]}},S=function(e){function r(){var e,i;(0,l.default)(this,r)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return i=(0,s.default)(this,(e=(0,c.default)(r)).call.apply(e,[this].concat(n))),(0,f.default)((0,u.default)(i),"renderValue",function(e){var t=i.props,n=t.ratio,a=t.distanceUnit,r=i.getValueRatio()
return m.default.createElement(y.default,(0,o.default)({ratio:n,unit:a,valueRatio:r},e))}),(0,f.default)((0,u.default)(i),"getValueRatio",function(){var e=i.props.selectedLayer,t=e.src_width,n=e.width
return t?t/n:1}),i}return(0,d.default)(r,e),(0,i.default)(r,[{key:"render",value:function(){var e=this.props,t=e.show,n=e.selectedLayer,a=e.hoveringLayer,r=e.screen
if(!t)return null
var i=b(n),o=a?b(a):{top:0,left:0,width:r.width,height:r.height}
return m.default.createElement(v.default,{baseRect:i,refRect:o,screen:r,renderValue:this.renderValue,theme:"preview"})}}]),r}(m.default.Component)
S.propTypes={show:h.default.bool,selectedLayer:h.default.object,hoveringLayer:h.default.object,screen:h.default.object}
var w=S
t.default=w},KKmY:function(e,t,n){},KUpD:function(e,t,n){e.exports={"install-page-wrapper":"_3INFrWQbU2BBH5IPDv0aSv","install-page":"SSwFfJxlXtECHTgNLr7PZ"}},Kgn6:function(e,t,n){"use strict"
var o=void 0
!function(t){var l,s={},c={16:!1,18:!1,17:!1,91:!1},n="all",u={"⇧":16,shift:16,"⌥":18,alt:18,option:18,"⌃":17,ctrl:17,control:17,"⌘":91,command:91},a={backspace:8,tab:9,clear:12,enter:13,return:13,esc:27,escape:27,space:32,left:37,up:38,right:39,down:40,del:46,delete:46,home:36,end:35,pageup:33,pagedown:34,",":188,".":190,"/":191,"`":192,"-":189,"=":187,";":186,"'":222,"[":219,"]":221,"\\":220},d=function(e){return a[e]||e.toUpperCase().charCodeAt(0)},f=[]
for(l=1;l<20;l++)a["f"+l]=111+l
function p(e,t){for(var n=e.length;n--;)if(e[n]===t)return n
return-1}function h(e,t){if(e.length!=t.length)return!1
for(var n=0;n<e.length;n++)if(e[n]!==t[n])return!1
return!0}var m={16:"shiftKey",18:"altKey",17:"ctrlKey",91:"metaKey"}
function r(e){var t,n,a,r,i,o
if(t=e.keyCode,-1==p(f,t)&&f.push(t),93!=t&&224!=t||(t=91),t in c)for(a in c[t]=!0,u)u[a]==t&&(v[a]=!0)
else if(function(e){for(l in c)c[l]=e[m[l]]}(e),v.filter.call(this,e)&&t in s)for(o=g(),r=0;r<s[t].length;r++)if((n=s[t][r]).scope==o||"all"==n.scope){for(a in i=0<n.mods.length,c)(!c[a]&&-1<p(n.mods,+a)||c[a]&&-1==p(n.mods,+a))&&(i=!1);(0!=n.mods.length||c[16]||c[18]||c[17]||c[91])&&!i||!1===n.method(e,n)&&(e.preventDefault?e.preventDefault():e.returnValue=!1,e.stopPropagation&&e.stopPropagation(),e.cancelBubble&&(e.cancelBubble=!0))}}function v(e,t,n){var a,r
a=y(e),void 0===n&&(n=t,t="all")
for(var i=0;i<a.length;i++)r=[],1<(e=a[i].split("+")).length&&(r=b(e),e=[e[e.length-1]]),e=e[0],(e=d(e))in s||(s[e]=[]),s[e].push({shortcut:a[i],scope:t,method:n,key:a[i],mods:r})}for(l in u)v[l]=!1
function g(){return n||"all"}function y(e){var t
return""==(t=(e=e.replace(/\s/g,"")).split(","))[t.length-1]&&(t[t.length-2]+=","),t}function b(e){for(var t=e.slice(0,e.length-1),n=0;n<t.length;n++)t[n]=u[t[n]]
return t}function e(e,t,n){e.addEventListener?e.addEventListener(t,n,!1):e.attachEvent&&e.attachEvent("on"+t,function(){n(window.event)})}e(document,"keydown",function(e){r(e)}),e(document,"keyup",function(e){var t,n=e.keyCode,a=p(f,n)
if(0<=a&&f.splice(a,1),93!=n&&224!=n||(n=91),n in c)for(t in c[n]=!1,u)u[t]==n&&(v[t]=!1)}),e(window,"focus",function(){for(l in c)c[l]=!1
for(l in u)v[l]=!1})
var i=t.key
t.key=v,t.key.setScope=function(e){n=e||"all"},t.key.getScope=g,t.key.deleteScope=function(e){var t,n,a
for(t in s)for(n=s[t],a=0;a<n.length;)n[a].scope===e?n.splice(a,1):a++},t.key.filter=function(e){var t=(e.target||e.srcElement).tagName
return!("INPUT"==t||"SELECT"==t||"TEXTAREA"==t)},t.key.isPressed=function(e){return"string"==typeof e&&(e=d(e)),-1!=p(f,e)},t.key.getPressedKeyCodes=function(){return f.slice(0)},t.key.noConflict=function(){var e=t.key
return t.key=i,e},t.key.unbind=function(e,t){var n,a,r,i,o,l=[]
for(n=y(e),i=0;i<n.length;i++){if(1<(a=n[i].split("+")).length&&(l=b(a)),e=a[a.length-1],e=d(e),void 0===t&&(t=g()),!s[e])return
for(r=0;r<s[e].length;r++)(o=s[e][r]).scope===t&&h(o.mods,l)&&(s[e][r]={})}},void 0!==o&&(o.exports=v)}(window)},Kkl0:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.enterLayer=t.ENTER_LAYER=t.activateLayer=t.ACTIVATE_LAYER=t.selectLayer=t.SELECT_LAYER=t.requestSelectLayer=t.REQUEST_SELECT_LAYER=void 0
var a="REQUEST_SELECT_LAYER"
t.REQUEST_SELECT_LAYER=a
t.requestSelectLayer=function(e){!(1<arguments.length&&void 0!==arguments[1])||arguments[1]
return{type:a,payload:{layerID:e}}}
var r="SELECT_LAYER"
t.SELECT_LAYER=r
t.selectLayer=function(e){return{type:r,payload:{layerID:e}}}
var i="ACTIVATE_LAYER"
t.ACTIVATE_LAYER=i
t.activateLayer=function(e){return MB.event("preview","点击了 Layer 元素"),{type:i,payload:{layerID:e}}}
var o="ENTER_LAYER"
t.ENTER_LAYER=o
t.enterLayer=function(e){return{type:o,payload:{layerID:e}}}},Kurm:function(e,t,n){e.exports={"full-screen-actions":"_2lLtO5YYxmdjnpavi3vbxH"}},KwMD:function(e,t){e.exports=function(e,t,n,a){for(var r=e.length,i=n+(a?1:-1);a?i--:++i<r;)if(t(e[i],i,e))return i
return-1}},L0cU:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("4dyd")),m=r(n("xtk/")),v=n("/N2d"),g=n("MURh"),y=function(e){function t(e){var n
return(0,i.default)(this,t),n=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(n),"setContainerRef",function(e){return n.$container=e}),(0,d.default)((0,c.default)(n),"updateContainerRect",function(){return n.setState({containerRect:n.$container.getBoundingClientRect()})}),(0,d.default)((0,c.default)(n),"handleScroll",function(){return n.updateContainerRect()}),(0,d.default)((0,c.default)(n),"handleResize",function(){return n.updateContainerRect()}),(0,d.default)((0,c.default)(n
),"handleScrollIntoView",function(e){var t=n.state.containerRect
n.$container.scrollTop+=e.top-t.top}),n.state={containerRect:null},n}return(0,u.default)(t,e),(0,o.default)(t,[{key:"componentDidMount",value:function(){this.updateContainerRect()}},{key:"render",value:function(){var n=this,e=this.props,t=e.screenList,a=e.projectToken,r=e.activeScreenCid,i=e.className,o=e.screenTimestampMap,l=e.onClickScreenItem,s=e.treeProps,c=e.editingCid,u=e.hoverCid,d=this.state.containerRect
return p.default.createElement(g.StyledThumbnailList,{ref:this.setContainerRef,className:i,onScroll:this.handleScroll},p.default.createElement("ol",{className:"thumbnail-list"},0===t.length&&p.default.createElement("div",{className:"not-match"},I18N.preview_panel.not_match),t.map(function(e,t){return p.default.createElement(m.default,{key:e.cid,screen:e,isEditing:e.cid===c,isHover:e.cid===u,projectToken:a,version:o[e.cid],canvasZoom:(0,v.getScreenThumbnailZoom)(e.width,e.height),isActive:e.cid===r,
containerRect:d,onActivate:l,scrollIntoView:n.handleScrollIntoView,treeProps:s})})),p.default.createElement(h.default,{onResize:this.handleResize}))}}]),t}(p.PureComponent);(t.default=y).propTypes={className:f.default.string,screenList:f.default.array,projectToken:f.default.string,editingCid:f.default.string,hoverCid:f.default.string,activeScreenCid:f.default.string,screenTimestampMap:f.default.object,onClickScreenItem:f.default.func,treeProps:f.default.object},y.defaultProps={screenTimestampMap:{}}},
Lyer:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var d=r(n("pVnL")),f=r(n("QILm")),o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),p=r(n("7W2i")),h=r(n("lSNA")),i=r(n("17x9")),m=a(n("q1tI")),v=n("6XO9"),g=r(n("rwIS")),y=function(e){return MB.localStorageDelegate.setItem("guide_closed_".concat(e),!0)},b=function(e){function i(){var e,r;(0,o.default)(this,i)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return r=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(n))),(0,h.default)((0,u.default)(r),"setGuideRef",function(e){return r.guide=e}),(0,h.default)((0,u.default)(r),"handleCloseGuideManually",function(){y(r.props.id)}),(0,h.default)((0,u.default)(r),"autoClose",function(){var e=r.props,t=e.duration,n=e.autoClose,a=e.id
e.isOpen&&t&&(r.timer=setTimeout(function(){n(),y(a)},t))}),r}return(0,p.default)(i,e),(0,l.default)(i,[{key:"componentDidUpdate",value:function(e){e.isOpen!==this.props.isOpen&&this.autoClose()}},{key:"componentWillUnmout",value:function(){clearTimeout(this.timer)}},{key:"render",value:function(){var e=this.props,t=e.id,n=e.isOpen,a=e.children,r=e.localeKey,i=e.position,o=e.className,l=(0,f.default)(e,["id","isOpen","children","localeKey","position","className"])
if(function(e){return"true"===MB.localStorageDelegate.getItem("guide_closed_".concat(e))}(t))return a
var s=I18N.guide_base[r||t],c=s.header,u=s.content
return m.default.createElement(v.Guide,(0,d.default)({ref:this.setGuideRef,isOpen:n,position:i,onClose:this.handleCloseGuideManually,className:"".concat(g.default["guide-button"]," ").concat(o),header:c,guide:m.default.createElement("div",{dangerouslySetInnerHTML:{__html:u}}),X:"right"},l),a)}}]),i}(m.PureComponent);(t.default=b).propTypes={id:i.default.string.isRequired,isOpen:i.default.bool,duration:i.default.number,localeKey:i.default.string,children:i.default.element,autoClose:i.default.func,
className:i.default.string,position:i.default.string},b.defaultProps={gotItText:I18N.guide_base.got_it}},MGhH:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.footerFilter=t.headerFilter=void 0
var r=a(n("MVZn")),i=n("0k54")
t.headerFilter=function(e,t){var n=e.children.filter(function(e){return 0===e.widget.primary_fixed&&("group"!==e.type?e.widget.t()<t:(0,i.getTreeBoundingRect)(e).minY<t)})
return(0,r.default)({},e,{children:n})}
t.footerFilter=function(e,n,a){var t=e.children.filter(function(e){if(0!==e.widget.primary_fixed)return!1
var t=n-e.widget.b()
return"group"!==e.type?t<a:n-(0,i.getTreeBoundingRect)(e).maxY<a})
return(0,r.default)({},e,{children:t})}},MURh:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledThumbnailList=void 0
var r=a(n("vOnD")),i=n("mggN"),o=r.default.div.withConfig({displayName:"styles__StyledThumbnailList",componentId:"sc-8dwe2g-0"})([
"width:100%;height:100%;overflow-x:hidden;overflow-y:auto;.thumbnail-list{display:flex;flex-wrap:wrap;width:calc(100% + 15px);color:#415058;.thumbnail-item{display:flex;flex-direction:column;justify-content:space-between;align-items:center;width:85px;position:relative;margin-right:10px;margin-bottom:10px;cursor:pointer;.Tooltip{width:100%;}.image-wrapper{width:100%;height:93px;padding:2px;background-color:",";border:1px solid ",
";border-radius:2px;display:flex;justify-content:center;align-items:center;transition:all 0.2s ease-out;img{max-width:100%;max-height:100%;pointer-events:none;}.toggle-comment{position:absolute;right:0;top:0;line-height:10px;transform:none;}.actions{display:none;position:absolute;z-index:1;top:4px;right:4px;height:24px;justify-content:space-around;align-items:center;&.is-hover{display:flex;}}&:hover,&.hover{border-width:2px;border-color:#79baff;padding:1px;.actions{display:flex;}}}.screen-name{height:26px;max-width:100%;line-height:26px;"
,";}&.active .image-wrapper{border-width:1px;border-color:#1e98ea;padding:2px;box-shadow:0 0 1px 0 rgba(34,162,237,0.66);}}}.not-match{width:100%;text-align:center;}"],function(e){return e.theme.thumbnail.bg},function(e){return e.theme.thumbnail.border_color},i.textEllipsis)
t.StyledThumbnailList=o},Mn07:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("RIqP")),p=r(n("17x9")),h=a(n("q1tI")),m=r(n("L0cU")),v=function(e){function t(e){var r
return(0,i.default)(this,t),r=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(r),"handleActivateScreen",function(e){var t=r.props,n=t.activeCid,a=t.dispatch
e!==n&&a({type:"entry:sync-runner:set-screen",payload:{cid:e}})}),r.treeProps={renderItem:e.renderCommentIcon},r}return(0,u.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.activeCid,n=function a(e,r,i){var o=i[e]?[i[e]]:[]
return r[e]&&r[e].forEach(function(e){var t=e.cid,n=a(t,r,i)
o.push.apply(o,(0,f.default)(n))}),o}("root",e.screenTreeMap,e.screenDataMap)
return h.default.createElement(m.default,{screenList:n,projectToken:MB.currentProject.access_token,activeScreenCid:t,onClickScreenItem:this.handleActivateScreen,treeProps:this.treeProps})}}]),t}(h.PureComponent)
t.default=v,(0,d.default)(v,"propTypes",{activeCid:p.default.string,screenTreeMap:p.default.object,screenDataMap:p.default.object,renderCommentIcon:p.default.func,dispatch:p.default.func})},NcbO:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=r(n("ibhU")),m=r(n("UbMB")).default.bind(h.default),v=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"handleBack",function(){return t.props.dispatch({type:"entry:runner:back-to-prev-page"})}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props.runnerState,o=e.activeCid,t=e.transition,n=e.history,a=e.screenInfoMap
if(!o)return null
var r=Screen.find(o)
return p.default.createElement("div",{className:m("runner-state-panel")},p.default.createElement("div",{className:"debug-title"},p.default.createElement("button",{onClick:this.handleBack},"上一页"),p.default.createElement("span",null,"当前页面: ".concat(r.name))),p.default.createElement("div",{className:"debug-info"},p.default.createElement("div",null,"访问历史:"),n.map(function(e){return p.default.createElement("span",{key:e},Screen.find(e).name)})),p.default.createElement("div",{className:"debug-info"},
p.default.createElement("div",null,"页面切换动画:"),p.default.createElement("span",null,"name: ".concat(t.name)),p.default.createElement("span",null,"duration: ".concat(t.duration)),p.default.createElement("span",null,"delay: ".concat(t.delay))),p.default.createElement("ul",null,Object.values(a).map(function(e){var t=e.cid,n=e.stateCid,a=e.transition,r=e.panelInfoMap,i=e.chameleonInfoMap
return p.default.createElement("li",{key:t,className:m({highlight:t===o})},p.default.createElement("span",null,Screen.find(t).name),p.default.createElement("span",null,"当前状态: ".concat(n)),p.default.createElement("span",null,"动画: ".concat(JSON.stringify(a))),p.default.createElement(g,{panelInfoMap:r}),p.default.createElement(y,{chameleonInfoMap:i}))})))}}]),i}(p.PureComponent)
t.default=v,(0,f.default)(v,"propTypes",{runnerState:i.default.object,dispatch:i.default.func})
var g=function(e){var t=e.panelInfoMap
return 0<Object.keys(t).length&&p.default.createElement("div",{style:{paddingLeft:10}},p.default.createElement("span",{style:{color:"green",marginTop:10}},"页面母版:"),p.default.createElement("ul",null,Object.values(t).map(function(e){var t=e.cid,n=e.activeScreenCid,a=e.transition,r=e.panelScreens
return console.log({cid:t}),p.default.createElement("li",{key:t},p.default.createElement("span",null,Panel.find(t).display_name),p.default.createElement("span",null,"当前母版页面: ".concat(n)),p.default.createElement("span",null,"动画: ".concat(JSON.stringify(a))),p.default.createElement("span",null,"已加载页面"),p.default.createElement("ul",null,r.map(function(e){return p.default.createElement("li",{key:e,className:m({active:e===n})},e)})))})))},y=function(e){var t=e.chameleonInfoMap
return 0<Object.keys(t).length&&p.default.createElement("div",{style:{paddingLeft:10}},p.default.createElement("span",{style:{color:"blue",marginTop:10}},"状态母版:"),p.default.createElement("ul",null,Object.values(t).map(function(e){var t=e.cid,n=e.stateCid,a=e.transition
return console.log({cid:t}),p.default.createElement("li",{key:t},p.default.createElement("span",null,Panel.find(t).display_name),p.default.createElement("span",null,"当前母版状态: ".concat(n)),p.default.createElement("span",null,"动画: ".concat(JSON.stringify(a))))})))}},NkXT:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var c=r(n("pVnL")),i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("PJYZ")),s=r(n("7W2i")),f=r(n("lSNA")),p=r(n("o0o1")),h=r(n("yXPU")),m=n("17x9"),v=a(n("q1tI")),g=n("i6OX"),y=n("t3Un"),b=n("rbsZ"),S=r(n("PeD6")),w=r(n("KUpD")),E=r(n("UbMB")).default.bind(w.default),k=function(){var t=(0,h.default)(p.default.mark(function e(t){var n,a,r
return p.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return MB.event("preview","移动端: 点击下载 APK"),e.next=3,(0,y.requestJSON)("/app/".concat(t,"/build/apk.json"),null,{method:"PUT"})
case 3:return e.next=6,C(5e3)
case 6:return e.next=8,(0,y.requestJSON)("/app/".concat(t,"/status/apk.json"))
case 8:if(n=e.sent,a=n.progress,r=n.link,100!==a)return e.abrupt("continue",3)
e.next=13
break
case 13:return window.location=r,e.abrupt("return")
case 17:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}(),C=function(t){return new Promise(function(e){return setTimeout(e,t)})},x=function(e){function t(){var s
return(0,i.default)(this,t),s=(0,l.default)(this,(0,u.default)(t).call(this)),(0,f.default)((0,d.default)(s),"handleView",function(e){e.preventDefault(),s.props.loadProject()}),(0,f.default)((0,d.default)(s),"handleInstall",function(e){e.preventDefault()
var t=s.props,n=t.projectAccessToken,a=t.isProjectExportable
MB.isWechat()?s.setState({isCoverShow:!0}):MB.isiPad()||MB.isIOS()?s.setState({isCoverShow:!0}):a?(s.setState({isCoverShow:!0}),k(n).then(function(){return s.setState({isCoverShow:!1})},function(e){})):(0,b.openRenewModal)("apk_exportable_on_mobile",{action:null})}),(0,f.default)((0,d.default)(s),"handleOpenCover",function(){s.setState({isCoverShow:!0})}),(0,f.default)((0,d.default)(s),"handleCloseCover",function(){s.setState({isCoverShow:!1})}),(0,f.default)((0,d.default)(s),"handleClickViewInClient",
function(e,t){MB.event("preview","移动端: 点击下载".concat(t,"客户端")),setTimeout(function(){window.location=e},200)}),(0,f.default)((0,d.default)(s),"handleHideNotice",function(){s.setState({isNoticeShow:!0})}),(0,f.default)((0,d.default)(s),"renderViewInClient",function(){var e={}
if(MB.isWechat())e={onClick:s.handleOpenCover}
else{var t=window.location,n=t.hostname,a=t.pathname,r=s.props,i=r.projectEncryptedPassword,o=r.urlClientIOS,l=r.urlClientAndroid
MB.isIOS()&&(e={href:"modao://".concat(n).concat(a,"?password=").concat(i),onClick:function(){s.handleClickViewInClient(o,"iOS")}}),MB.isAndroid()&&(e={href:"intent://".concat(n).concat(a,"?password=").concat(i,"#Intent;package=com.mockingbot;scheme=mockingbot;S.browser_fallback_url=").concat(encodeURIComponent(l),";end"),onClick:function(){s.handleClickViewInClient(l,"Android")}})}return v.default.createElement("a",(0,c.default)({className:"install-btn primary"},e),I18N.open_in_client)}),s.state={
isCoverShow:!1,isNoticeShow:!1},s}return(0,s.default)(t,e),(0,o.default)(t,[{key:"componentDidMount",value:function(){window.$("#splash").hide(),window.$("#workspace").show(),window.$.timeago.settings.lang=window.MBLocale,window.$(".timeago").timeago()}},{key:"render",value:function(){var e=this.props,t=e.projectName,n=e.projectIconUrl,a=e.projectUpdatedAt,r=this.state,i=r.isCoverShow,o=r.isNoticeShow
return v.default.createElement("div",{className:E("install-page-wrapper")},v.default.createElement("div",{className:E("install-page",{"is-wechat":MB.isWechat()})},v.default.createElement("div",{className:E("app-notice",{"hide-notice":o})},v.default.createElement(g.SVGIcon,{className:"app-warning",name:"design/warning"}),v.default.createElement("p",{className:"notice-content"},"iOS/安卓移动客户端已更新，请及时更新版本以查看企业项目。"),v.default.createElement("a",{className:"app-times",onClick:this.handleHideNotice},
v.default.createElement(g.SVGIcon,{name:"times"}))),v.default.createElement("div",{className:"app-inner"},v.default.createElement("img",{className:"app-icon",src:n}),v.default.createElement("h1",{className:"app-name"},t),v.default.createElement("div",{className:"app-update-time"},v.default.createElement("time",{className:"timeago",dateTime:a}),I18N.update),v.default.createElement("div",{className:"install-btns"},this.renderViewInClient(),v.default.createElement("a",{className:"install-btn",
onClick:this.handleView},I18N.view_app)),v.default.createElement("a",{className:"download-btn",onClick:this.handleInstall},v.default.createElement("span",null,MB.isAndroid()?I18N.download_android_apk:I18N.add_to_home_screen),v.default.createElement("i",{className:"fa fa-angle-right"}))),v.default.createElement(S.default,{show:i,onClose:this.handleCloseCover})))}}]),t}(v.PureComponent)
t.default=x,(0,f.default)(x,"propTypes",{projectAccessToken:m.PropTypes.string,projectEncryptedPassword:m.PropTypes.string,projectName:m.PropTypes.string,projectIconUrl:m.PropTypes.string,projectUpdatedAt:m.PropTypes.string,isProjectExportable:m.PropTypes.bool,urlClientIOS:m.PropTypes.string,urlClientAndroid:m.PropTypes.string,loadProject:m.PropTypes.func})},Nu6V:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.fetchSliceZip=t.default=void 0
var a=n("t3Un")
t.default=function(e){return(0,a.requestJSON)("".concat("/api/v2","/sketch/slices.json?project_cid=").concat(e))}
t.fetchSliceZip=function(e){return(0,a.requestJSON)("".concat("/api/v2","/sketch/slices/build_zip.json?project_cid=").concat(e),null,{method:"POST"})}},NyBV:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(e){return MB.localStorageDelegate.getItem(m)?null:p.default.createElement(i,e)}
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),h=n("6XO9")
n("bTYh")
var i=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"state",{isOpen:!0}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"componentDidMount",value:function(){var e=this
setTimeout(function(){e.setState({isOpen:!1}),MB.localStorageDelegate.setItem(m,!0)},4e3)}},{key:"render",value:function(){var e=this.state.isOpen
return p.default.createElement(h.Guide,{className:"commercial-font-tip",isOpen:e,noCloseBtn:!0,guide:I18N.commercial_font_tip_preview,X:"center",Y:"top"})}}]),i}(p.Component)
var m="commercialFontTipShownInPreview"},OVdA:function(e,t,n){e.exports={"text-wrapper":"_2Q7780091rmwUdJheR5GPh","text-no-editing":"_1KyFLtyjq2MMPQk1NN80C7"}},P3rE:function(e,t,n){},PeD6:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=n("17x9"),p=a(n("q1tI")),h=r(n("ldhK")),m="/images/sharing/wechat_".concat(window.MBLocale,".png"),v="/images/sharing/ios_".concat(window.MBLocale,".png"),g=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"handleClick",function(){t.props.onClose()}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props.show,t=MB.isWechat(),n=!t&&MB.isIOS(),a=MB.isiPad(),r=!(t||n),i={display:e?"":"none"}
return p.default.createElement("div",{className:h.default.covers,style:i,onClick:this.handleClick},t&&p.default.createElement("div",{className:"cover wechat"},p.default.createElement("img",{className:"robot",src:"/images/sharing/robot.png"}),p.default.createElement("img",{className:"tips",src:m}),"s",p.default.createElement("div",{className:"arrow"})),n&&!a&&p.default.createElement("div",{className:"cover ios"},p.default.createElement("img",{className:"robot",src:"/images/sharing/robot.png"}),
p.default.createElement("img",{className:"tips",src:v}),p.default.createElement("div",{className:"arrow"})),a&&p.default.createElement("div",{className:"cover ipad"},p.default.createElement("img",{className:"robot",src:"/images/sharing/robot.png"}),p.default.createElement("img",{className:"tips",src:v}),p.default.createElement("div",{className:"arrow"})),r&&p.default.createElement("div",{className:"cover building"},p.default.createElement("div",{className:"tip-wrapper"},p.default.createElement("p",{
className:"tip"},I18N.building_apk),p.default.createElement("div",{className:"spinner"}))))}}]),i}(p.PureComponent);(t.default=g).propTypes={show:i.PropTypes.bool,onClose:i.PropTypes.func}},PqLM:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.lineIsParallelWithAxis=t.getLineAttrsAfterRotate=t.getLineAttrsAsWidget=t.getLineAttrsAfterUngroup=t.getVectorInOtherSystem=t.degreeToRadians=t.getLength=t.getAngle=t.getLineAngle=t.getLineGeneralInfo=void 0
var P=a(n("J4zp")),C=function(e){e.top,e.left
var t=e.width,n=e.height,a=e.bs,r=e.points,i=1<arguments.length&&void 0!==arguments[1]&&arguments[1],o=Math.sqrt(t*t+n*n),l=a,s=JSON.parse(r).map(function(e){return e.point}),c=u(t,n,s)
return{length:i?Math.round(o):o,angle:i?Math.round(c)%360:c,thickness:l}}
t.getLineGeneralInfo=C
var u=function(e,t,n){var a=(0,P.default)(n,2),r=a[0],i=a[1],o=(i[0]-r[0])*e,l=(i[1]-r[1])*t
return s(o,l)}
t.getLineAngle=u
var s=function(e,t){var n=r(e,t)
return 0===n?0:0<=e?(360+i(Math.asin(t/n)))%360:180-i(Math.asin(t/n))}
t.getAngle=s
var r=function(e,t){return Math.sqrt(e*e+t*t)}
t.getLength=r
var i=function(e){return 180*e/Math.PI},x=function(e){return e/180*Math.PI}
t.degreeToRadians=x
var I=function(e,t){var n=(0,P.default)(e,2),a=n[0],r=n[1],i=x(t)
return[Math.cos(i)*a+Math.sin(i)*r,-Math.sin(i)*a+Math.cos(i)*r]}
t.getVectorInOtherSystem=I
t.getLineAttrsAfterUngroup=function(e,t,n,a){var r=(0,P.default)(e,2),i=r[0],o=r[1],l=(0,P.default)(t,2),s=l[0],c=l[1],u=a.top,d=a.left,f=a.width,p=a.height,h=a.points,m=JSON.parse(h).map(function(e){return e.point}),v=(0,P.default)(m,2),g=(0,P.default)(v[0],2),y=g[0],b=g[1],S=(0,P.default)(v[1],2),w=S[0],E=S[1],k=[d-s,u-c],C=[k[0]+w*f,k[1]+E*p],x=I([k[0]+y*f,k[1]+b*p],-n),T=I(C,-n),_=[i+x[0],o+x[1]],M=[i+T[0],o+T[1]]
return N(_,M)}
var N=function(e,t){var n=(0,P.default)(e,2),a=n[0],r=n[1],i=(0,P.default)(t,2),o=i[0],l=i[1],s=Math.min(r,l),c=Math.min(a,o),u=Math.abs(o-a),d=Math.abs(l-r),f=[[0===u?.5:(a-c)/u,0===d?.5:(r-s)/d],[0===u?.5:(o-c)/u,0===d?.5:(l-s)/d]].map(function(e){return{point:e}})
return{top:Math.round(s),left:Math.round(c),width:Math.max(Math.round(u),1),height:Math.max(Math.round(d),1),points:JSON.stringify(f)}}
t.getLineAttrsAsWidget=N
t.getLineAttrsAfterRotate=function(e,t){var n=2<arguments.length&&void 0!==arguments[2]?arguments[2]:0,a=x(t),r=e.top,i=e.left,o=e.width,l=e.height,s=e.points,c=JSON.parse(s).map(function(e){return e.point}),u=(0,P.default)(c,2),d=(0,P.default)(u[0],2),f=d[0],p=d[1],h=(0,P.default)(u[1],2),m=h[0],v=h[1],g=C(e).length,y=[i+o*f,r+l*p],b=[i+o*m,r+l*v],S=[y[0]+(b[0]-y[0])*n,y[1]+(b[1]-y[1])*n],w=[y[0]+g*Math.cos(a),y[1]+g*Math.sin(a)],E=[y[0]+(w[0]-y[0])*n,y[1]+(w[1]-y[1])*n],k=[S[0]-E[0],S[1]-E[1]]
return N([y[0]+k[0],y[1]+k[1]],[w[0]+k[0],w[1]+k[1]])}
t.lineIsParallelWithAxis=function(e){var t=(0,P.default)(e,2),n=(0,P.default)(t[0],2),a=n[0],r=n[1],i=(0,P.default)(t[1],2),o=i[0],l=i[1]
return.5===a&&.5===o||.5===r&&.5===l}},QdB0:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=o.find(function(e){var t=e.checker
return t()})
return e?e.info:null}
var r=a(n("ThAd")),i={info:{name:"lisankebook",desc:"李三科送给你的专属福利，现在注册墨刀即可享受一个月个人版会员",successTip:"注册成功，恭喜你获得墨刀一个月个人版会员"},checker:function(){return(0,r.default)().utm_source===i.info.name}},o=[i]},Ro3d:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.transfromProptype=void 0
var D=a(n("lSNA")),r=n("XrEr"),O=n("qOCw")
t.transfromProptype=function(e){var t=e.attr,n=e.language,a=e.unit,r=(0,O.selectWithlanguageUnit)(n),i=t.width,o=t.height,l=t.lineHeight,s=t.opacity,c=t.borderRadius,u=t.borderWidth,d=t.borderColor,f=t.backgroundColor,p=t.color,h=t.fontSize,m=t.fontFamily,v=t.fontStyle,g=t.boxShadow,y=t.textAlign,b=t.x,S=t.y,w=b&&(0,D.default)({},q[r].x,F(b,a,r)),E=S&&(0,D.default)({},q[r].y,F(S,a,r)),k=i&&(0,D.default)({},q[r].width,F(i,a,r)),C=o&&(0,D.default)({},q[r].height,F(o,a,r)),x=l&&(0,D.default)({},q[r].lineHeight
,F(l,a,r)),T=s&&(0,D.default)({},q[r].opacity,F(s,a,r)),_=c&&(0,D.default)({},q[r].borderRadius,F(c,a,r)),M=f&&(0,D.default)({},q[r].backgroundColor,F(f,a,r,!0)),P=p&&(0,D.default)({},q[r].color,F(p,a,r,!0)),I=h&&(0,D.default)({},q[r].fontSize,F(h,a,r)),N=m&&(0,D.default)({},q[r].fontFamily,F(m,a,r)),R=v&&(0,D.default)({},q[r].fontStyle,F(v,a,r)),L=g&&(0,D.default)({},q[r].shadows,g),j=u&&(0,D.default)({},q[r].borderWidth,F(u,a,r)),A=d&&(0,D.default)({},q[r].borderColor,F(d,a,r,!0)),B=y&&(0,D.default)({},
q[r].textAlign,y)
return Object.assign({},w,E,k,C,x,T,_,j,A,M,P,I,R,B,L,N)}
var F=function(e,t,n){var a=3<arguments.length&&void 0!==arguments[3]&&arguments[3]
return e=e.toString(),"pt"!==n?e.replace(t,n):a?(0,r.getUIColor)(e):e.replace(t,"")},q={px:{x:"left",y:"top",width:"width",height:"height",lineHeight:"line-height",opacity:"opacity",border:"border",borderRadius:"border-radius",borderColor:"border-color",borderWidth:"border-width",backgroundColor:"background-color",color:"color",fontSize:"font-size",fontFamily:"font-family",fontStyle:"font-style",textAlign:"text-align",shadows:"box-shadow",innerShadows:"inner-shadow"},dp:{x:"left",y:"top",
width:"layout_width",height:"layout_height",border:"border",opacity:"opacity",color:"textColor",fontSize:"textSize",fontFamily:"font-family",fontStyle:"font-style",textAlign:"gravity",backgroundColor:"background",borderRadius:"radius",borderColor:"border-color",lineHeight:"line-height",borderWidth:"border-width",shadows:"box-shadow",innerShadows:"inner-shadow"},pt:{x:"x",y:"y",width:"width",height:"height",opacity:"opacity",border:"border",backgroundColor:"backgroundColor",color:"text-color",
textAlign:"alignment",fontSize:"fontSize",fontFamily:"fontFamily",fontStyle:"font-style",borderRadius:"cornerRadius",borderColor:"borderColor",borderWidth:"border-width",lineHeight:"lineSpacing"}}},RtVw:function(e,t,n){e.exports={fullscreen:"_1yqBFlDRjPD3syHb3ZboIK"}},S7Zs:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.fetchArtboardsByProjectCid=void 0
var a=n("t3Un")
t.fetchArtboardsByProjectCid=function(e){return window.MBArtboards?{artboards:Object.values(window.MBArtboards).map(function(e){return e.artboard})}:(0,a.requestJSON)("".concat("/api/v2/sketch","/artboards.json?project_cid=").concat(e))}},S9rr:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledScrollBar=void 0
var r=a(n("vOnD")).default.div.withConfig({displayName:"styles__StyledScrollBar",componentId:"sc-1i763xb-0"})(["position:absolute;top:",";left:",";right:0;bottom:0;z-index:4;pointer-events:none;.track{position:absolute;background:",
";pointer-events:auto;.handler{position:absolute;cursor:pointer;.thumb{position:absolute;pointer-events:none;border-radius:4px;transition:background 0.2s ease-in-out;}}}.x-track{left:0;right:11px;bottom:0;height:12px;.handler{bottom:2px;height:10px;.thumb{bottom:0;width:100%;height:6px;background:",";}}}.y-track{top:0;bottom:11px;right:0;width:12px;.handler{right:2px;width:10px;.thumb{right:0;height:100%;width:6px;background:",";}}}.x-track .handler:hover .thumb{background:",
";}.y-track .handler:hover .thumb{background:",";}"],"17px","17px",function(e){return e.theme.scrollbar.track.bg},function(e){return e.theme.scrollbar.thumb.x_bg},function(e){return e.theme.scrollbar.thumb.y_bg},function(e){return e.theme.scrollbar.thumb.x_hover_bg},function(e){return e.theme.scrollbar.thumb.y_hover_bg})
t.StyledScrollBar=r},SFPg:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var k=r(n("pVnL")),C=r(n("J4zp")),i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),d=r(n("17x9")),x=a(n("q1tI")),T=r(n("vmbo")),_=n("/5+U"),f=function(e){function E(){return(0,i.default)(this,E),(0,l.default)(this,(0,s.default)(E).apply(this,arguments))}return(0,c.default)(E,e),(0,o.default)(E,[{key:"render",value:function(){var e=this.props,t=e.layer,n=e.parentRect,a=e.treeProps,r=t.width,i=t.height,o=t.top,l=t.left,s=t.z,c=t.childrenLayers
if(!1===t.v)return null
var u="layer"===t.kind?0:t.rotation||0,d=(0,_.getMinBoundingRect)({width:r,height:i,rotate:u,top:o,left:l}),f=(0,C.default)(d,4),p=f[0],h=f[1],m=f[2],v=f[3],g={top:o,left:l,width:r,height:i},y=h,b=m,S=v,w={top:(p-n.top)/n.height*100+"%",left:(y-n.left)/n.width*100+"%",width:b/n.width*100+"%",height:S/n.height*100+"%",zIndex:s||0}
return x.default.createElement("div",{"data-id":t.id,className:"layer-tree-node",style:w},x.default.createElement(T.default,(0,k.default)({layer:t},a)),c&&0<c.length&&c.map(function(e){return x.default.createElement(E,{key:e.id,layer:e,parentRect:g,treeProps:a})}))}}]),E}(x.Component)
t.default=f,(0,u.default)(f,"propTypes",{layer:d.default.object,parentRect:d.default.object,treeProps:d.default.object})},SVae:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.requestSnapshotZipLocalhost=t.requestSnapshotLocalhost=t.requestThumbnailLocalhost=void 0
var d=a(n("QILm")),f=a(n("o0o1")),p=a(n("yXPU")),h=n("VtqW"),s=n("xV1f"),m=window.URLSearchParams,v=function(){var t=(0,p.default)(f.default.mark(function e(t){var n,a,r,i,o,l=arguments
return f.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:n=1<l.length&&void 0!==l[1]?l[1]:250,2<l.length&&void 0!==l[2]?l[2]:5e3,a=3<l.length&&void 0!==l[3]?l[3]:1/0,r=n,i=0
case 5:if(i<a)return e.next=8,(0,s.setTimeoutAsync)(r)
e.next=17
break
case 8:return e.next=10,t()
case 10:if(o=e.sent)return e.abrupt("return",o)
e.next=13
break
case 13:i+=r,r+=n,e.next=5
break
case 17:throw new Error("reach retry limit: ".concat(a))
case 18:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.requestThumbnailLocalhost=function(e){var n=e.imageElement,a=e.projectAccessToken,r=e.screenCid,t=e.screenStateCid,i=void 0===t?"default":t,o=e.mode,l=void 0===o?"thumbnail":o
return new Promise(function(e,t){n.onerror=function(){n.src="/images/preview/image-load.png",t()},n.onload=function(){return e(n)},n.src="".concat("/snapshot.png","?").concat(new m({"access-token":a,"screen-cid":r,"screen-state-cid":i,mode:l}))})}
var r=function(){var t=(0,p.default)(f.default.mark(function e(t){var n,a,r,i,o,l,s,c,u
return f.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.projectAccessToken,a=t.screenCid,r=t.canvasZoom,i=void 0===r?1:r,o="/app/".concat(n,"/build/png.json?").concat(new m({cid:a,scale:100*i})),e.next=4,(0,h.fetchLikeRequest)(o,{method:"PUT"})
case 4:return e.next=6,e.sent.json()
case 6:if(l=e.sent,s=l.taskId,100!==(c=(0,d.default)(l,["taskId"])).progress)return u="/app/".concat(n,"/status/png.json?").concat(new m({task_id:s,cid:a,scale:100*i})),e.next=13,v((0,p.default)(f.default.mark(function e(){return f.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,h.fetchLikeRequest)(u)
case 2:return e.next=4,e.sent.json()
case 4:return c=e.sent,e.abrupt("return",100===c.progress&&c)
case 6:case"end":return e.stop()}},e)})),250,1e3,3e4)
e.next=14
break
case 13:c=e.sent
case 14:return e.abrupt("return",c)
case 15:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.requestSnapshotLocalhost=r
var i=function(){var t=(0,p.default)(f.default.mark(function e(t){var n,a,r,i,o,l,s,c,u
return f.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.projectAccessToken,a=t.canvasZoom,r=void 0===a?1:a,i=t.onProgress,o="/app/".concat(n,"/build/pngs.json?").concat(new m({scale:100*r})),e.next=4,(0,h.fetchLikeRequest)(o,{method:"PUT"})
case 4:return e.next=6,e.sent.json()
case 6:if(l=e.sent,s=l.taskId,100!==(c=(0,d.default)(l,["taskId"])).progress)return u="/app/".concat(n,"/status/pngs.json?").concat(new m({task_id:s,scale:100*r})),e.next=13,v((0,p.default)(f.default.mark(function e(){return f.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,h.fetchLikeRequest)(u)
case 2:return e.next=4,e.sent.json()
case 4:return c=e.sent,i&&i(c.progress),e.abrupt("return",100===c.progress&&c)
case 7:case"end":return e.stop()}},e)})),250,5e3,6e5)
e.next=14
break
case 13:c=e.sent
case 14:return e.abrupt("return",c)
case 15:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.requestSnapshotZipLocalhost=i},TZdj:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("WVP6"),r=n("Ehhz").MODEL_OPERATION_MAP.Comment,i=(0,a.createStateStore)([]),o=i.getState,l=i.setState,s=i.wrapEntry,c=function(i,o){return s(function(e,t,n){var a=t.dispatch,r=n&&n.payload
a({type:"reducer:comments:update",payload:i(e,r,o)})})},u={entryMap:{"comments:refresh":c(r.refreshStateList,!1),"comments:add":c(r.addState,!1),"comments:add-local":c(r.addState,!0),"comments:update":c(r.updateState,!1),"comments:update-local":c(r.updateState,!0),"comments:delete":c(r.deleteState,!1),"comments:delete-local":c(r.deleteState,!0)},getState:o,setState:l}
t.default=u},ThAd:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=location.search
0===e.indexOf("?")&&(e=e.substr(1))
var i={}
return e.split("&").forEach(function(e){var t=e.split("="),n=(0,o.default)(t,2),a=n[0],r=n[1]
a&&(i[a]=!r||decodeURIComponent(r))}),i}
var o=a(n("J4zp"))},TjoA:function(e,t,n){e.exports={"distance-measurement-container":"ofVDlkqpF9Yunky2QkBPn"}},U9kS:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),Object.defineProperty(t,"CommentHeaderGlobalStyle",{enumerable:!0,get:function(){return g.CommentHeaderGlobalStyle}}),t.CommentThread=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),v=a(n("q1tI")),d=r(n("17x9")),f=r(n("vOnD")),p=r(n("zkrS")),h=n("l0oT"),m=n("FC/4"),g=n("6iHT"),y=p.default.MB,b=p.default.I18N,S=function(e){function n(e){var t
return(0,i.default)(this,n),(t=(0,l.default)(this,(0,s.default)(n).call(this,e))).focusThread=function(){return!t.props.isScrollFocus&&t.props.commentOperations.setHoverFocusCommentThreadCid(t.props.commentThreadCid)},t.blurThread=function(){return t.props.isBlur&&t.props.commentOperations.setHoverFocusCommentThreadCid(null)},t.setRef=function(e){t.mainRef=e},t.mainRef=null,t.toggleUnfoldComment=function(){t.setState({isUnfold:!t.state.isUnfold}),y.event("preview","展开评论")},t.state={isUnfold:!1},t}return(0,
c.default)(n,e),(0,o.default)(n,[{key:"componentDidUpdate",value:function(e){if(this.props.commentList.length>e.commentList.length&&this.setState({isUnfold:!0}),this.props.isScrollFocus&&this.props.isScrollFocus!==e.isScrollFocus&&this.mainRef){var t=this.mainRef.parentElement,n=t.getBoundingClientRect().top,a=t.scrollTop+this.mainRef.getBoundingClientRect().top-n;(0,h.scrollTo)(t,a,20)}}},{key:"render",value:function(){var e=this.props,t=e.commentList,n=e.permission,a=e.commentMarkerIndex,
r=e.commentOperations,i=e.isBlur
if(!t.length)return null
var o=this.state.isUnfold,l=t[0],s=3<t.length,c=o||!s?t.slice(1):t.slice(1,3)
return v.default.createElement(w,{ref:this.setRef,className:i?"comment-blur":"",onMouseEnter:this.focusThread,onMouseLeave:this.blurThread},v.default.createElement(k,{markIndex:a,comment:l,permission:n,commentOperations:r}),c.map(function(e){return v.default.createElement(k,{sub:!0,key:e.cid,comment:e,permission:r.getPermission(e.user_id),commentOperations:r})}),s&&v.default.createElement("div",{className:"unfold",onClick:this.toggleUnfoldComment},o?b.preview.comment.fold:b.preview.comment.unfold))}}]),n}(
v.PureComponent)
t.CommentThread=S,(0,u.default)(S,"propTypes",{permission:d.default.object,isScrollFocus:d.default.bool,isBlur:d.default.bool,commentList:d.default.array,commentMarkerIndex:d.default.number,commentThreadCid:d.default.string,commentOperations:d.default.object})
var w=f.default.div.withConfig({displayName:"CommentLayerThread__CommentThreadDiv",componentId:"sc-18dqjl1-0"})(["width:220px;padding:20px 0;&.comment-blur{opacity:0.4;}& > .unfold{cursor:pointer;display:flex;justify-content:flex-end;}"]),E=f.default.div.withConfig({displayName:"CommentLayerThread__EntryMainBgDiv",componentId:"sc-18dqjl1-1"})(["width:100%;margin-bottom:10px;border-radius:4px;background:#f7f7fa;"]),k=function(e){function t(e){var n
return(0,i.default)(this,t),(n=(0,l.default)(this,(0,s.default)(t).call(this,e))).operationPack={getCommentValue:function(){return n.props.comment.message},doCreateComment:function(e){return e&&n.props.commentOperations.doCreateComment(e,n.props.comment.thread_cid)},doUpdateComment:function(e){return n.props.commentOperations.doUpdateComment({cid:n.props.comment.cid,message:e})},doDeleteCard:function(){return n.props.sub?n.props.commentOperations.doDeleteComment(n.props.comment
):n.props.commentOperations.doDeleteCommentThread(n.props.comment.thread_cid)}},n.startEdit=function(){n.setState({editStore:(0,m.createTextEditStore)({value:n.operationPack.getCommentValue(),isEditing:!0},{onEnd:function(e){var t=e.value
t=(t||"").trim(),n.operationPack.doUpdateComment(t),n.closeEdit()}})}),y.event("preview","二次编辑")},n.closeEdit=function(){return n.setState({editStore:null})},n.startReply=function(){return n.setState({replyStore:(0,m.createTextEditStore)({isEditing:!0},{onChange:function(e){var t=e.value
return n.setState({isValidReply:Boolean(t)})},onEnd:function(e){var t=e.value;(t=(t||"").trim())&&n.operationPack.doCreateComment(t),n.closeReply()}})})},n.closeReply=function(){return n.setState({replyStore:null,isValidReply:!1})},n.state={editStore:null,replyStore:null,isValidReply:!1},n}return(0,c.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.sub,n=e.markIndex,a=e.comment,r=e.permission,i=e.commentOperations,o=this.state,l=o.editStore,s=o.replyStore,c=o.isValidReply,
u=i.getUserProfile(a.user_id),d=u.avatar,f=u.name,p=v.default.createElement(g.ContentMessage,{sub:t,comment:a,textEditStore:l,cancelEdit:this.closeEdit}),h=!l&&(0,g.commonContentFooter)(a,s,c,r.create&&this.startReply,this.closeReply),m=t?l?"sub remove-background":"sub":""
return v.default.createElement(C,{className:m},v.default.createElement(g.ContentHeader,{sub:t,avatar:d,name:f,markIndex:n,startEdit:!l&&r.update?this.startEdit:null,doDelete:!l&&r.delete?this.operationPack.doDeleteCard:null}),!t&&v.default.createElement(E,null,p,h),t&&p,t&&h)}}]),t}(v.PureComponent);(0,u.default)(k,"propTypes",{sub:d.default.bool,markIndex:d.default.number,comment:d.default.object.isRequired,permission:d.default.object.isRequired,commentOperations:d.default.object.isRequired})
var C=f.default.div.withConfig({displayName:"CommentLayerThread__CommentCardDiv",componentId:"sc-18dqjl1-2"})(["display:flex;flex-flow:column;border-radius:4px;&.sub{margin:0 0 10px 20px;width:200px;background:#f7f7fa;}&.remove-background{background:#fff;}"])},UJpD:function(e,t,n){e.exports={detector:"_2Wbc2EU813xLnapfNPnrUi"}},ULaQ:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=n("G4qV"),o=n("upRB"),l=a(n("EWR0")),s=(0,i.createSelector)([o.getRunnerState],function(e){return{runnerState:e}}),c=(0,r.connect)(function(e){return s(e)})(l.default)
t.default=c},UUBB:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),i=r(n("17x9")),h=n("vbsp"),m=r(n("TSYQ")),v=function(e){function i(){var e,n;(0,o.default)(this,i)
for(var t=arguments.length,a=new Array(t),r=0;r<t;r++)a[r]=arguments[r]
return n=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(n),"handleChange",function(e){if(!n.props.disabled&&!e.currentTarget.classList.contains("disabled")){var t=e.currentTarget.dataset.value
n.props.handleChange(t)}}),(0,f.default)((0,u.default)(n),"getBgStyle",function(e,t){var n=0===e,a=e===t-1
if(0<=e)return{transform:"translateX(".concat(100*e,"%)"),borderLeftColor:n?"transparent":"",borderRightColor:a?"transparent":""}}),n}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var l=this,e=this.props,t=e.options,s=e.value,n=e.disabled,a=e.className,c=t.findIndex(function(e){return e.value===s}),u=this.getBgStyle(c,t.length)
return p.default.createElement(h.StyledRadioLine,{className:(0,m.default)("radio-line",a,{disabled:n})},t.map(function(e,t){var n=e.label,a=e.value,r=e.compatibleValues,i=e.disabled,o=!i&&(r?r.includes(s):s===a)
return p.default.createElement("li",{className:(0,m.default)("radio-option",{active:o},{disabled:i}),key:a,"data-value":a,onClick:l.handleChange},0===t&&p.default.createElement("div",{className:(0,m.default)("move-cube",{active:0<=c}),style:u}),p.default.createElement("div",{className:"radio-content"},n))}))}}]),i}(p.PureComponent);(t.default=v).propTypes={options:i.default.arrayOf(i.default.shape({label:i.default.node,value:i.default.any})),className:i.default.string,value:i.default.any,
disabled:i.default.bool,handleChange:i.default.func}},UfWW:function(e,t,n){var i=n("KwMD"),o=n("ut/Y"),l=n("Sxd8"),s=Math.max
e.exports=function(e,t,n){var a=null==e?0:e.length
if(!a)return-1
var r=null==n?0:l(n)
return r<0&&(r=s(a+r,0)),i(e,o(t,3),r)}},Ur7v:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("pVnL")),o=r(n("MVZn")),l=r(n("o0o1")),s=r(n("yXPU")),c=r(n("lwsE")),u=r(n("W8MJ")),d=r(n("a1gu")),f=r(n("Nsbk")),p=r(n("PJYZ")),h=r(n("7W2i")),m=r(n("lSNA")),v=r(n("Znm+")),g=r(n("mwIZ")),y=a(n("q1tI")),b=r(n("17x9")),S=n("/MKj"),w=n("7Qib"),E=n("wYtL"),k=r(n("i6OX")),C=n("5vJs"),x=n("xoLq"),T=n("/5+U"),_=r(n("ztWx")),M=function(e){function t(){var n
return(0,c.default)(this,t),n=(0,d.default)(this,(0,f.default)(t).call(this)),(0,m.default)((0,p.default)(n),"handleShare",(0,s.default)(l.default.mark(function e(){return l.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:MB.isDashboard?MB.askDashboardToShare():n.setState({isSharingOverlayOpen:!0}),MB.event("preview","工具栏: 点击分享按钮"),MB.event("zhuge",(0,T.canBackToWorkspace)()?"Preview_click_share":"LinkPreview_click_share"),MB.event("zhuge","SharePopup_enter",{From:(0,T.canBackToWorkspace)(
)?"Preview":"Linkpreview"})
case 4:case"end":return e.stop()}},e)}))),(0,m.default)((0,p.default)(n),"onToggleSharingOverlay",function(e){var t=(0,v.default)(e)?e:!n.state.isOpen
t||MB.event("zhuge","运行页-预览-分享弹窗",{"边框类型":MB.project().shell_type,"链接高亮":MB.project().highlight?"开启":"关闭"}),n.setState({isSharingOverlayOpen:t})}),(0,m.default)((0,p.default)(n),"updateTeam",function(e){MB.currentTeam=(0,w.snakizeKeys)((0,o.default)({},MB.currentTeam,e)),n.forceUpdate()}),(0,m.default)((0,p.default)(n),"updateApp",function(e){MB.currentProject=(0,w.snakizeKeys)((0,o.default)({},MB.currentProject,e)),n.forceUpdate()}),n.state={isSharingOverlayOpen:!1},n}return(0,h.default)(t,e),(0,u.default
)(t,[{key:"render",value:function(){var e=this.sharingOverlay
return y.default.createElement(y.Fragment,null,y.default.createElement(E.Tooltip,{position:"bottom",duration:1e3,content:{hover:I18N.preview.share},tipClassName:"marign-top-20"},y.default.createElement(k.default,{type:"dora",name:"share",className:"share-icon",onClick:this.handleShare})),e)}},{key:"data",get:function(){var e=(0,w.camelizeKeys)(MB.currentOrg),t=(0,w.camelizeKeys)(MB.currentTeam),n=(0,w.camelizeKeys)(MB.currentProject),a=MB.user,r=a.id,i=(0,g.default)(e,"cid","me"),o=n.expired
return e&&Object.assign(e,{policyPermissionMap:C.POLICY_PERMISSION_MAP}),{workspace:i,isExpired:o,org:e,team:t,app:n,me:a,meId:r}}},{key:"sharingOverlay",get:function(){var e=this.state.isSharingOverlayOpen,t=this.data
return!MB.isDashboard&&y.default.createElement(_.default,(0,i.default)({isOpen:e,onToggle:this.onToggleSharingOverlay,updateTeamFromProps:this.updateTeam,updateAppFromProps:this.updateApp},t,{withStore:!1}))}}]),t}(y.PureComponent);(0,m.default)(M,"propTypes",{checkPermissionStorelessly:b.default.func})
var P=(0,S.connect)(void 0,{checkPermissionStorelessly:x.checkPermissionStorelessly})(M)
t.default=P},"Uu/L":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledScreenItem=t.StyledScreenList=void 0
var r=a(n("vOnD")),i=n("mggN"),o=r.default.ul.withConfig({displayName:"styles__StyledScreenList",componentId:"sc-1v51q5m-0"})(["&,ol,li{list-style:none;}.not-match{width:100%;text-align:center;}"])
t.StyledScreenList=o
var l=r.default.div.withConfig({displayName:"styles__StyledScreenItem",componentId:"sc-1v51q5m-1"})([""," .screen-name{display:flex;align-items:center;width:100%;padding-right:5px;.icon{flex-shrink:0;margin-right:4px;}span{",";}}.actions{padding:0 10px;.actions-ellipsis{font-size:14px;pointer-events:none;}&:hover{.actions-ellipsis{color:#298df8;}}}.child-screens{position:relative;}&.wait-hover *{pointer-events:none;}&.linking{color:",";background:#bbd8fe;.actions{display:none;}}"],i.listItem,i.textEllipsis,
function(e){return e.theme.listItem.tc})
t.StyledScreenItem=l},VQzC:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.fetchProjectComment=void 0
var s=a(n("o0o1")),r=a(n("yXPU")),c=n("VtqW"),u=a(n("zkrS")).default.MB,i=function(){var t=(0,r.default)(s.default.mark(function e(t){var n,a,r,i,o,l
return s.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.projectCid,a=t.projectAccessToken,e.next=3,(0,c.fetchLikeRequest)("/api/v2/sharing/".concat(n,"/comments?password=").concat(u.localStorageDelegate.getItem("".concat(a,"_pwd"))||""))
case 3:if(r=e.sent,i=r.ok,o=r.status,l=r.json,i){e.next=9
break}throw new Error("[fetchProjectComment] invalid status: ".concat(o))
case 9:return e.next=11,l()
case 11:return e.abrupt("return",e.sent)
case 12:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.fetchProjectComment=i},Vk5q:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.onFallbackError=t.doFallbackSaveItem=t.onSocketError=t.doSocketBatchSave=t.getSaveItemInfo=t.processSaveQueue=void 0
var u=a(n("o0o1")),r=a(n("yXPU")),d=n("VtqW"),s=n("xV1f"),c=n("t77w"),f=n("ycqN"),p=window.MB
t.processSaveQueue=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:[],a={},r=[]
e.forEach(function(e){var t=e.record,n="".concat(t.constructor.className,"-").concat(t.cid)
void 0===a[n]&&(a[n]=r.length),r[a[n]]=e})
var n=new Set
return r.forEach(function(e){var t=e.record
return e.isDelete&&["Widget","Panel"].includes(t.constructor.className)&&n.add(t.cid)}),r.filter(function(e){var t=e.record
return!("Widgetstate"===t.constructor.className&&n.has(t.widget_cid)||"Panelstate"===t.constructor.className&&n.has(t.panel_cid))}).map(function(e){var t=e.record,n=e.isDelete,a=t.constructor.className,r=n?"DELETE":"Asset"===a?"POST":"PUT",i="POST"==r?"/".concat(a.toLowerCase(),"s"):"/".concat(a.toLowerCase(),"s/").concat(encodeURIComponent(t.id)),o=JSON.stringify("DELETE"==r?{cid:t.cid,mtime:t.mtime}:(0,c.compressRichText)(t.toJSON())),l={className:a,cid:t.cid}
return"Panel"===a&&Template.find(t.template_cid),{url:i,method:r,body:o,extraInfo:l}})}
t.getSaveItemInfo=function(e){var t=e.url,n=e.method,a=e.body
return JSON.stringify({url:t,method:n,bodyLength:a?a.length:0})}
var i=function(){var t=(0,r.default)(u.default.mark(function e(t){var n,a,r
return u.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.saveChunk,t.attempt,t.timeout,a=p.project()?p.project().template?p.project().project_cid:p.project().cid:"",r={id:p.user.id,name:p.user.name,avatar:p.user.avatar},e.next=5,p.Pusher.requestBatchSave({batchSaveQueue:n,rootProjectCid:a,fromUser:r})
case 5:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.doSocketBatchSave=i
var o=function(){var n=(0,r.default)(u.default.mark(function e(t,n){var a,r
return u.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(a=n.saveChunk,n.attempt,r=n.timeout,t.message&&t.message.toLowerCase().includes("timeout"))return p.event("ga-0","send","event","batch-saving","batch saving timeout","(".concat(a.length,")(").concat(r,"ms)(").concat(p.user.email,")")),p.alertAsync({title:I18N.error_happened,desc:I18N.network_error,isHTML:!0}),e.next=7,(0,s.setTimeoutAsync)(5e3)
e.next=9
break
case 7:e.next=12
break
case 9:return p.event("ga-0","send","event","batch-saving","batch saving error: ".concat(t.status),"[".concat(t.status,"] ").concat(t.message||t,": (").concat(a.length,"item|").concat(r,"ms)(").concat(p.user.email,")")),e.next=12,(0,f.SAVE_NUKE_SEQUENCE)(t,t.status)
case 12:case"end":return e.stop()}},e)}))
return function(e,t){return n.apply(this,arguments)}}()
t.onSocketError=o
var l=function(){var t=(0,r.default)(u.default.mark(function e(t){var n,a,r,i,o,l,s,c
return u.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.saveItem,a=n.url,r=n.method,i=n.body,o=t.attempt,l=t.timeout,e.next=3,(0,d.fetchLikeRequest)(a,{headers:{"Content-Type":"application/json"},method:r,body:i,timeout:l})
case 3:if(s=e.sent,200!==(c=s.status))return p.event("ga-0","send","event","saving","saving error: ".concat(c),"".concat(c,": ").concat(a,"(").concat(r,"|x").concat(o,"|").concat(l,"ms)(").concat(p.user.email,")")),e.next=9,(0,f.SAVE_NUKE_SEQUENCE)(new Error("fallback saving error: ".concat(c)),c)
e.next=9
break
case 9:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.doFallbackSaveItem=l
var h=function(){var n=(0,r.default)(u.default.mark(function e(t,n){var a,r,i,o,l
return u.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return a=n.saveItem,r=a.url,i=a.method,o=n.attempt,l=n.timeout,p.event("ga-0","send","event","saving","fallback saving error: ".concat(t.message||t),"".concat(t.message||t,": ").concat(r,"(").concat(i,"|x").concat(o,"|").concat(l,"ms)(").concat(p.user.email,")")),p.alertAsync({title:I18N.error_happened,desc:I18N.network_error,isHTML:!0}),e.next=6,(0,s.setTimeoutAsync)(5e3)
case 6:case"end":return e.stop()}},e)}))
return function(e,t){return n.apply(this,arguments)}}()
t.onFallbackError=h},WcC0:function(e,t,n){},XKAG:function(e,t,n){var l=n("ut/Y"),s=n("MMmD"),c=n("7GkX")
e.exports=function(o){return function(e,t,n){var a=Object(e)
if(!s(e)){var r=l(t,3)
e=c(e),t=function(e){return r(a[e],e,a)}}var i=o(e,t,n)
return-1<i?a[r?e[i]:i]:void 0}}},XpKX:function(e,t,n){e.exports={"mb-preview-page":"HpPhB83xskCxzhv6pRWDy","is-offline-mode":"_28_YiE-2ulr1BboXRcKxWW","is-uichina":"pxVKuNMBIglIQCw1n6NBA"}},Y69h:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var g=a(n("MVZn")),y=a(n("J4zp")),i=a(n("lwsE")),o=a(n("W8MJ")),l=a(n("a1gu")),s=a(n("Nsbk")),c=a(n("PJYZ")),u=a(n("7W2i")),b=a(n("lSNA")),S=a(n("q1tI")),r=a(n("17x9")),d=n("1qiG"),f=function(e){function r(){var e,v;(0,i.default)(this,r)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return v=(0,l.default)(this,(e=(0,s.default)(r)).call.apply(e,[this].concat(n))),(0,b.default)((0,c.default)(v),"getDistanceMarksStyle",function(e,t){return{top:(0,d.toPercentage)(e.top/t.height),left:(0,d.toPercentage)(e.left/t.width),width:(0,d.toPercentage)(e.width/t.width),height:(0,d.toPercentage)(e.height/t.height)}}),(0,b.default)((0,c.default)(v),"mapDistanceMarks",function(e,t){var n,a=(0,y.default)(e,2),r=a[0],i=a[1],o=v.props,l=o.style,s=o.renderValue,c=l.showStartAndEndBoundary,u=l.colorForLines
,d=l.colorForText,f=l.backgroundColorForText,p=l.dashed,h=v.getMarkStyle(r,i),m=Math.abs(i)
return S.default.createElement("div",{key:"".concat(t,"-").concat(i)},S.default.createElement("div",{className:"distance-line ".concat(r),style:(0,g.default)({},h.line,(n={},(0,b.default)(n,["top","bottom"].includes(r)?"borderLeftStyle":"borderTopStyle",p?"dashed":"solid"),(0,b.default)(n,"borderColor",u),n))}),s?s({value:m,style:h.value,customClassName:"distance-value ".concat(r)}):S.default.createElement("span",{className:"distance-value ".concat(r),style:(0,g.default)({},h.value,{color:d,
backgroundColor:f})},m),c&&S.default.createElement(S.default.Fragment,null,S.default.createElement("div",{className:"distance-mark-start-boundary ".concat(r),style:{borderColor:u}}),S.default.createElement("div",{className:"distance-mark-end-boundary ".concat(r),style:(0,g.default)({},h.endBoundary,{borderColor:u})})))}),(0,b.default)((0,c.default)(v),"getMarkStyle",function(e,t){var n,a=v.props.baseRect,r={line:{},value:{},endBoundary:{}},i=["right","left"],o=i.includes(e)?t/a.width:t/a.height
return r.line=(n={},(0,b.default)(n,e,t<0?0:(0,d.toPercentage)(-o)),(0,b.default)(n,i.includes(e)?"width":"height",(0,d.toPercentage)(Math.abs(o))),n),r.endBoundary=(0,b.default)({},e,(0,d.toPercentage)(-o)),r.value=(0,b.default)({},i.includes(e)?"left":"top",["right","bottom"].includes(e)?(0,d.toPercentage)(1+o/2):(0,d.toPercentage)(-o/2)),r}),v}return(0,u.default)(r,e),(0,o.default)(r,[{key:"render",value:function(){var e=this.props,t=e.baseRect,n=e.refRect,a=e.screen,r=(0,d.getDistancesForDirections)(t,n
),i=this.getDistanceMarksStyle(t,a)
return S.default.createElement("div",{className:"distance-marks",style:i},Object.entries(r).map(this.mapDistanceMarks))}}]),r}(S.default.Component);(t.default=f).propTypes={baseRect:r.default.object,refRect:r.default.object,screen:r.default.object,style:r.default.object,renderValue:r.default.func}},YCqe:function(e,t,n){e.exports={"debug-panel":"_2FC9CioQVPnHdqZbgEIKH7"}},YwNm:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=a(n("MVZn")),l=n("upRB"),s={useTransform:!1,disableTouch:!1,disablePointer:!0,preventDefault:!0,ignoreEventException:function(e){var t=$(e.target).closest(".widget")
if(t.length){if(t.hasClass("webpage"))return!0
if(t.hasClass("map_view"))return!0
if(t.find("input").length)return!0}var n=$(e.target).closest(".ppanel")
if(n.length){var a=Panel.find(n.data("cid")),r=a.getState(MB.currentScreen.state_cid),i=a.ct()
if(i.height>r.height||i.width>r.width)return!0}return!1}},c=(0,o.default)({},s,{probeType:3,scrollbars:!0,mouseWheel:!0,disableMouse:!1,interactiveScrollbars:!0,shrinkScrollbars:"scale",fadeScrollbars:!0,HWCompositing:!1}),u=function(){function e(){(0,r.default)(this,e),this.iScrollMap={}}return(0,i.default)(e,[{key:"clear",value:function(){this.destroyScrollBar()}},{key:"setObjectUrl",value:function(e,t){e&&(e.contentWindow?e.contentWindow.location.replace(t):e.setAttribute("src",t))}},{key:"deviceOrient",
value:function(){return $(window).width()>$(window).height()?"landscape":"portrait"}},{key:"toggleScrollBar",value:function(t){Object.values(this.iScrollMap).forEach(function(e){t?e.enable():e.disable()})}},{key:"renderScrollbar",value:function(e){this.iScrollMap[e]?this._refreshScrollBar(e):this._initScrollBar(e)}},{key:"_initScrollBar",value:function(e){if(!this.iScrollMap[e]){var n=document.querySelector("#pscreen".concat(e," .screen-content"))
if(!n)throw new Error("初始化滚动条失败, 找不到对应的DOM元素"+e)
var t=MB.isMobile()?s:c,a=new window.IScroll(n,t),r=document.querySelector("#sticky-container")
r&&a.on("scroll",function(e){var t=n.querySelector(".widgets")
r.querySelector("#stickies").style.marginTop=t.style.top}),MB.isMobile()||$(n).on("wheel",function(e){n.offsetHeight!==n.scrollHeight&&e.stopPropagation()}),this.iScrollMap[e]=a}}},{key:"_refreshScrollBar",value:function(e){this.iScrollMap[e]&&this.iScrollMap[e].refresh()}},{key:"resetScreenScrollState",value:function(e){var t=this.iScrollMap[e]
t&&t.scrollTo(0,0)
var n=document.querySelector("#stickies")
n&&(n.style.marginTop=0)}},{key:"destroyScrollBar",value:function(){Object.values(this.iScrollMap).forEach(function(e){$(e.wrapper).off("wheel"),e.destroy()}),this.iScrollMap={}}},{key:"destroyScrollBarByCid",value:function(e){var t=this.iScrollMap[e]
t&&($(t.wrapper).off("wheel"),t.destroy(),delete this.iScrollMap[e])}},{key:"resetScrollState",value:function(){Object.values(this.iScrollMap).forEach(function(e){return e.scrollTo(0,0)})
var e=document.querySelector("#stickies")
e&&(e.style.marginTop=0)}},{key:"setupStatusBar",value:function(e){var t=$(".pcanvas.active .status_bar").removeClass("standalone light")
if(window.innerHeight>window.innerWidth){t.addClass("standalone")
var n=e.sb()
!n||n.th&&"light"!=n.th||t.addClass("light")}if(MB.isIOS9()&&this.deviceOrient()===e.orient()){var a=MB.COMPONENTS.status_bar.height
$("#app").css({top:0-a,height:window.innerHeight+a})}}},{key:"hideScreen",value:function(e){$(e).hide(),$(e).find(".iframe").each(function(e,t){MB.runner.runnerUtil.setObjectUrl(t,"about:blank")})}},{key:"getIsImmersive",value:function(){return(0,l.getIsImmersive)(MB.webpackInterface.store.getState())}},{key:"getIsHighlight",value:function(){return(0,l.getIsHighlight)(MB.webpackInterface.store.getState())}},{key:"getIsScreenExpanded",value:function(){return(0,l.getIsScreenExpanded)(
MB.webpackInterface.store.getState())}},{key:"getCurrentScreen",value:function(){var e=(0,l.getRunnerActiveScreenCid)(MB.webpackInterface.store.getState())
return Screen.find(e)}}]),e}()
t.default=u},Z3xQ:function(e,t,n){"use strict"
var a=n("TqRt")
n("oQ6s"),n("p/ml"),n("83sM"),n("tTzg"),n("Kgn6"),n("3y7X"),n("hQvp"),n("1gVK"),n("FTTL"),n("Tbyd"),n("r2ef"),n("ypWq"),n("DhCz"),n("ZjFo"),n("NlNL"),n("7xwf")
var r=a(n("zkrS"))
n("KKmY"),n("P3rE"),n("dppN"),n("T7iu")
var i=a(n("7eYF")),o=a(n("aqSL")),l=n("+Cau"),s=n("abHt")
n("RJdT"),n("20hc"),MB.COMPONENTS=s.componentMap
try{r.default.MB.webpackInterface=(0,i.default)(o.default),r.default.MB.messageBucket=(0,l.createMessageBucket)(l.receiverMap)}catch(e){console.warn("[UI:Preview] Failed to init:",e.stack||e)}},ZS4k:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=a(n("4sCl")),o=n("Kkl0"),l=(0,r.connect)(function(e){var t=e.container,n=t.common.keyFlags.isSpaceDown,a=t.layers,r=a.resourceByScreen,i=a.visibilityScreenID,o=a.activeLayerID,l=a.enteredLayerID,s=t.previewSetting,c=s.unit,u=s.ratio,d=s.isShowColorPicker,f=e.model,p=f.current.screenCid,h=f.screens.find(function(e){return e.cid===p})
return{isSpaceDown:n,layers:r[i]&&r[i].layers||[],artboard:r[i]&&r[i].artboard,currentScreen:h,activeLayerID:o,enteredLayerID:l,isShowLayerList:!d,unit:c,ratio:u}},function(t){return{requestSelectLayer:function(e){t((0,o.requestSelectLayer)(e))},enterLayer:function(e){t((0,o.enterLayer)(e))},handleShowlayerInfo:function(e){t({type:"reducer:preview-toolbar:update",payload:{isSelectLayer:e}})}}})(i.default)
t.default=l},ZY2Q:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.reducer=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:i,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"container:comment:loaded-project":return(0,r.default)({},e,{loadedProjectCid:a.projectCid||null,loadedProjectCommentData:a.projectCommentData||null})
case"container:comment:focus":return(0,r.default)({},e,{focusCommentThreadCid:a.focusCommentThreadCid,focusSource:a.focusSource||null,tempCommentThreadMarker:e.tempCommentThreadMarker&&e.tempCommentThreadMarker.cid===a.focusCommentThreadCid?e.tempCommentThreadMarker:null})
case"container:comment:focus-temp-marker":return(0,r.default)({},e,{focusCommentThreadCid:null,focusSource:null,tempCommentThreadMarker:a})}return e}
var r=a(n("MVZn")),i={loadedProjectCid:null,loadedProjectCommentData:null,focusCommentThreadCid:null,focusSource:null,tempCommentThreadMarker:null}},"Zu+4":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("PJYZ")),o=r(n("lSNA")),l=r(n("lwsE")),s=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("7W2i")),y=a(n("q1tI")),f=r(n("17x9")),p=n("vOnD"),h=r(n("i6OX")),b=n("wYtL"),m=r(n("QdB0")),S=r(n("5Mi5")),w=r(n("ULaQ")),E=r(n("Aa0X")),k=r(n("18l9")),C=r(n("jZq5")),x=r(n("DJvY")),T=r(n("DdUa")),_=r(n("2AqR")),M=r(n("nQhf")),P=r(n("xUDz")),I=r(n("NyBV")),N=r(n("ewu5")),R=r(n("mdx/")),v=r(n("gY5R")),L=n("1iCU"),g=r(n("XpKX")),j=r(n("UbMB")),A=n("/5+U"),B=j.default.bind(g.default),D=window,O=D.MB,F=D.I18N,
q=new Set(["ai@mockingbot.com","ethantw@me.com"]),W=function(e){function t(){return(0,l.default)(this,t),(0,c.default)(this,(0,u.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,s.default)(t,[{key:"render",value:function(){return y.default.createElement(p.ThemeProvider,{theme:v.default.light},y.default.createElement(U,this.props))}}]),t}(y.PureComponent)
t.default=W
var U=function(e){function r(e){var t;(0,l.default)(this,r),t=(0,c.default)(this,(0,u.default)(r).call(this,e)),(0,o.default)((0,i.default)(t),"handleClick",function(){V(),t.setState({showLoadtip:!1})})
var n=e.dispatch
n({type:"entry:init:preview:scale"}),n({type:"reducer:artboards:init"}),n({type:"preview:set:canvas:offset",payload:{offset:{x:0,y:0}}}),n({type:"entry:init:preview-setting"}),t.state={showLoadtip:!0}
var a=new URLSearchParams(location.search)
return a.has("inspect")?e.dispatch({type:"entry:preview:select",payload:{toolbarActiveItem:L.INSPECT}}):a.has("comment")?e.dispatch({type:"entry:preview:select",payload:{toolbarActiveItem:L.COMMENT}}):e.dispatch({type:"reducer:preview-toolbar:active-item:init"}),t}return(0,d.default)(r,e),(0,s.default)(r,[{key:"componentWillUnmount",value:function(){this.props.dispatch({type:"entry:preview:clear"})}},{key:"componentDidMount",value:function(){var e=(0,m.default)()
if(e){var t={open:!0,event:e}
this.props.dispatch({type:"event-sign-up:set:event",payload:t})}(0,A.canBackToWorkspace)()||O.event("zhuge","PreviewOrLinkPreview_enter",{User_id:"",ProjectCreator_id:O.currentProject.owner_id,via:"click",IF_User_ProjectCreator:!1,From:"Link"})}},{key:"render",value:function(){var e=this.props,t=e.isLite,n=e.project,a=e.previewSetting,r=e.isProjectFromOtherFreeUser,i=e.toastList,o=e.popupList,l=e.dispatch,s=this.state.showLoadtip
if(t)return y.default.createElement(y.default.Fragment,null,y.default.createElement(T.default,null),y.default.createElement(M.default,null))
var c=n.owner_email,u=n.master,d=a.toolbarActiveItem,f=a.isFullScreenMode,p=d==L.PREVIEW,h=d==L.INSPECT,m=!O.isElectron()&&!O.isHTMLZip()&&h&&s&&H(),v=!u&&p&&(q.has(c)||r),g=B("mb-preview-page",{"is-offline-mode":O.isHTMLZip(),"is-uichina":O.isUIChina()||O.isForum(),"full-screen":f})
return y.default.createElement("div",{className:g},y.default.createElement(_.default,null),f&&y.default.createElement(P.default,null),y.default.createElement("div",{id:"preview-content-container",className:"preview-content-container"},y.default.createElement(E.default,null),y.default.createElement(x.default,null),y.default.createElement(C.default,null),y.default.createElement(k.default,null)),v||O.isUIChina()&&y.default.createElement("a",{className:"powered-by",href:"/",target:"_blank"},
y.default.createElement("img",{className:"zh",src:"/images/preview/watermark_zh.svg",alt:F.preview.powered_by_modao}),y.default.createElement("img",{className:"en",src:"/images/preview/watermark_en.svg",alt:F.preview.powered_by_modao})),y.default.createElement(z,{isActive:m,onClick:this.handleClick}),p&&y.default.createElement(I.default,null),y.default.createElement(M.default,null),y.default.createElement(w.default,null),y.default.createElement(S.default,{dispatch:l}),y.default.createElement(
b.TooltipGlobalStyle,null),y.default.createElement(N.default,{toastList:i}),y.default.createElement(R.default,{popupList:o}))}}]),r}(y.Component);(0,o.default)(U,"propTypes",{isLite:f.default.bool,project:f.default.object,previewSetting:f.default.object,isProjectFromOtherFreeUser:f.default.bool,toastList:f.default.array,popupList:f.default.array,dispatch:f.default.func})
var z=function(e){var t=e.isActive,n=e.onClick
return t?y.default.createElement("div",{className:"download-client-tip"},y.default.createElement(h.default,{type:"fa",name:"info-circle",className:"download-client-tip-icon"}),y.default.createElement("span",{className:"download-text"},y.default.createElement("a",{href:"/downloads",rel:"noopener noreferrer",target:"_blank"},F.preview.client_load_a)," ",F.preview.client_load_tip),y.default.createElement(h.default,{type:"dora",name:"times_fc",className:"download-client-close-icon",onClick:n})):null}
z.propTypes={isActive:f.default.bool.isRequired,onClick:f.default.func.isRequired}
var Y="close_client_load_tip",H=function(){return!O.localStorageDelegate.getItem(Y)},V=function(){return O.localStorageDelegate.setItem(Y,"true")}},aYzi:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),d=n("1iCU"),i=n("/5+U"),o=a(n("Zu+4")),f=(0,i.immutableTransformCache)(function(e,t){return e.find(function(e){return e.cid===t})}),l=(0,r.connect)(function(e){var t=e.model,n=t.current,a=t.projects,r=e.container,i=r.previewSetting,o=r.toastList,l=r.popupList,s=i.toolbarActiveItem,c=f(a,n.projectCid),u=MB.isMobile()||MB.isEmbedded()
return{isLayerActive:s===d.INSPECT,isCommentActive:s===d.COMMENT,previewSetting:i,isProjectFromOtherFreeUser:n.userId!==c.owner_id&&c.expired,isLite:u,project:c,toastList:o,popupList:l}})(o.default)
t.default=l},aqSL:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("q1tI")),i=a(n("i8i4")),l=n("/MKj"),s=n("q3nj"),c=n("6x+O"),u=a(n("6ZRU")),o={containerReducerMap:s.reducerMap,sagaMap:s.sagaMap,extendCallback:function(o){o.renderPreview=function(e){var t=o.store
t.dispatch({type:"entry:init:preview:related:data"}),i.default.render(r.default.createElement(l.Provider,{store:t},r.default.createElement(s.PreviewContainer,null)),e)},o.renderPreviewAlert=function(){i.default.render(r.default.createElement(u.default.containers.Alert,{store:o.store}),(0,c.getModalElement)())},o.pushData=function(e,t,n){o.store.dispatch({type:"entry:state:push-data",payload:{pushType:e,action:t,data:n}})},o.checkLocationHash=function(){var e=window.location.hash||"",t=o.store,n=t.getState,
a=t.dispatch
if(e.startsWith("#thread=")){var r=e.substr("#thread=".length),i=n().model.commentThreads.find(function(e){return e.cid===r})
if(!i)return console.warn("[checkLocationHash] missing commentThread: ".concat(r))
a({type:"entry:sync-runner:set-screen",payload:{cid:i.screen_cid}}),a({type:"entry:comment:set:active",payload:{isActive:!0}}),a({type:"container:comment:focus",payload:{focusCommentThreadCid:i.cid}})}},o.updateCurrentScreenRunner=function(e){if(!e)return console.warn("[updateCurrentScreenRunner] missing currentScreen")
o.store.dispatch({type:"entry:current:set-screen",payload:e}),window.location.hash="#screen=".concat(e.cid)}}}
t.default=o},aw2M:function(e,t,n){},"ax+U":function(e,t){t.__esModule=!0
var r=function(e,t,n){return void 0===t&&(t=null),void 0===n&&(n=null),{value:e,prev:t,next:n}}
t.createNode=r,t.createDoublyLinkedList=function(){var i,o,l,e=function(){i=new Set,o=r(null),l=r(null),(o.next=l).prev=o}
e()
var t=function(e,t){var n=t.next
t.next=n.prev=e,e.prev=t,e.next=n,i.add(e)},n=function(e,t){var n=t.prev
t.prev=n.next=e,e.prev=n,e.next=t,i.add(e)},a=function(e){var t=e.prev,n=e.next;(t.next=n).prev=t,e.prev=e.next=null,i.delete(e)}
return{clear:e,getHead:function(){return o},getTail:function(){return l},getLength:function(){return i.size},insertAfter:t,insertBefore:n,remove:a,removeBetween:function(e,t){var n=e.prev,a=t.next;(n.next=a).prev=n,e.prev=t.next=null
for(var r=e;r;)i.delete(r),r=r.next},forEach:function(e){for(var t=o.next,n=0;t!==l;)e(t,n),t=t.next,n++},forEachReverse:function(e){for(var t=l.prev,n=i.size-1;t!==o;)e(t,n),t=t.prev,n--},reverse:function(){for(var e=o.next;e!==l;){var t=e,n=t.prev,a=t.next
e.prev=a,e.next=n,e=a}var r=o.next,i=l.prev
o.next=i,l.prev=r,i.prev=o,r.next=l},setFirst:function(e){if(e!==o.next){var t=e.prev,n=e.next;(t.next=n).prev=t,e.prev=o,e.next=o.next,o.next=e}},setLast:function(e){if(e!==l.prev){var t=e.prev,n=e.next;(t.next=n).prev=t,e.prev=l.prev,(e.next=l).prev=e}},push:function(e){return n(e,l)},pop:function(){return a(l.prev)},unshift:function(e){return t(e,o)},shift:function(){return a(o.next)}}}},bNtH:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),v=a(n("q1tI")),g=n("S9rr"),p=function(e){function t(){var y
return(0,i.default)(this,t),y=(0,l.default)(this,(0,s.default)(t).call(this)),(0,d.default)((0,c.default)(y),"handleScroll",function(e){e.stopPropagation()
var r=e.target.dataset.axis,i=e.clientX,o=e.clientY,t=y.props,n=t.canvasOffset,l=n.x,s=n.y,a=t.viewportHeight,c=t.viewportWidth,u=t.canvasRange,d=t.onScroll,f="x"===r?c:a,p=function(e){var t=e.clientY,n=e.clientX,a="x"===r?n-i:t-o
a=a/(f-f/u[r]*f)*u[r],d("x"===r?{x:l-a,y:s}:{x:l,y:s-a})}
document.addEventListener("mousemove",p),document.addEventListener("mouseup",function e(t){document.removeEventListener("mousemove",p),document.removeEventListener("mouseup",e)})}),(0,d.default)((0,c.default)(y),"handleClickTrack",function(e){var d=e.target.dataset.axis,f=e.clientX,p=e.clientY,t=y.props,h=t.onScroll,m=t.canvasRange,n=t.viewportHeight,a=t.viewportWidth,r=y.scrollbarX.getBoundingClientRect(),i=r.top,o=r.bottom,l=r.left,s=r.right,v="x"===d?y.scrollbarX:y.scrollbarY,g="x"===d?a:n,c=function(){
var e=v.getBoundingClientRect(),t=e.top,n=e.bottom,a=e.left,r=e.right,i=y.props.canvasOffset,o=i.x,l=i.y,s="x"===d?r<f:n<p,c="x"===d?f<a:p<t,u=(c?-1:s?1:0)*Math.min(m[d]/10,g);(s||c)&&h("x"===d?{x:o-u,y:l}:{x:o,y:l-u})};(("x"===d?s<f:o<p)||("x"===d?f<l:p<i))&&(v.style.transition="all 0.1s linear",c(),y.timer=setTimeout(function(){return y.timeInterval=setInterval(c,100)},500))
document.addEventListener("mouseup",function e(t){v.style.transition="",clearTimeout(y.timer),clearInterval(y.timeInterval),document.removeEventListener("mouseup",e)})}),y.setRefY=function(e){return y.scrollbarY=e},y.setRefX=function(e){return y.scrollbarX=e},y}return(0,u.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.canvasOffset,n=t.x,a=t.y,r=e.canvasRange,i=e.viewportWidth,o=e.viewportHeight,l=e.showRuler,s=i/r.x,c=(r.x/2-n)*(r.x-i)/(r.x*r.x)
c=Math.min(Math.max(c,0),(r.x-i)/r.x)
var u=o/r.y,d=(r.y/2-a)*(r.y-o)/(r.y*r.y)
d=Math.min(Math.max(d,0),(r.y-o)/r.y)
var f={width:"".concat(100*s,"%"),left:"".concat(100*c,"%")},p={height:"".concat(100*u,"%"),top:"".concat(100*d,"%")},h=l?null:{left:0},m=l?null:{top:0}
return v.default.createElement(g.StyledScrollBar,null,v.default.createElement("div",{"data-axis":"x",className:"track x-track",style:h,onMouseDown:this.handleClickTrack},v.default.createElement("div",{ref:this.setRefX,className:"handler","data-axis":"x",onMouseDown:this.handleScroll,style:f},v.default.createElement("div",{className:"thumb"}))),v.default.createElement("div",{"data-axis":"y",className:"track y-track",style:m,onMouseDown:this.handleClickTrack},v.default.createElement("div",{ref:this.setRefY,
className:"handler y-handler","data-axis":"y",onMouseDown:this.handleScroll,style:p},v.default.createElement("div",{className:"thumb"}))))}}]),t}(v.PureComponent)
t.default=p,(0,d.default)(p,"propTypes",{canvasOffset:f.default.object,canvasRange:f.default.object,viewportWidth:f.default.number,viewportHeight:f.default.number,showRuler:f.default.bool,onScroll:f.default.func}),(0,d.default)(p,"defaultProps",{showRuler:!1})},bTYh:function(e,t,n){},cQH5:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("MVZn")),i=a(n("4vJh")),o=a(n("FJlG")),l=a(n("vRqJ")),s=a(n("FYsW")),c=n("80la"),u=n("oose"),d=n("tBsX"),f=a(n("4x8W")),p=a(n("qTnY")),h=a(n("G1Xk")),m=a(n("6ZRU")),v={isSpaceDown:!1},g={offset:{x:0,y:0},scale:100,keyFlags:v,viewport:{width:0,height:0},preference:{}}
var y={toastList:p.default,popupList:h.default,alert:m.default.reducers,common:function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:g,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"preview:update:state":return(0,r.default)({},e,a)
case"preview:set:canvas:offset":return(0,r.default)({},e,{offset:a.offset})
case"preview:set:scale":return(0,r.default)({},e,{scale:a.scale})
case"preview:set:key:flags":return(0,r.default)({},e,{keyFlags:(0,r.default)({},v,a)})
case"preview:reset:key:flags":return(0,r.default)({},e,{keyFlags:v})
case"preview:scrollbar:viewport":return(0,r.default)({},e,{viewport:a})
default:return e}},comment:u.reducer,layers:d.reducers,slices:c.reducer,screens:i.default,artboards:l.default,previewSetting:o.default,eventSignUpModal:f.default,runner:s.default}
t.default=y},ctY3:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=r(n("OVdA")),m=r(n("UbMB")).default.bind(h.default),v=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"setElementRef",function(e){return t.textarea=e}),(0,f.default)((0,u.default)(t),"handleFocus",function(){t.props.onFocus()}),(0,f.default)((0,u.default)(t),"handleChange",function(e){(0,t.props.onChange)(e.target.value)}),(0,f.default)((0,u.default)(t),"handleBlur",function(){t.props.onBlur()}),(0,f.default)((0,u.default)(t),"handleKeyDown",function(e){"Enter"===e.key?(e.preventDefault(),
t.handleBlur()):"Escape"===e.key&&(t.props.onChange(t.cacheValue),t.cacheValue=null,t.handleBlur())}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"componentDidMount",value:function(){this.props.editing&&(this.cacheValue=this.props.value,this.textarea.select())}},{key:"componentDidUpdate",value:function(e,t){!e.editing&&this.props.editing&&(this.cacheValue=this.props.value,this.textarea.select())}},{key:"handleStopPropagation",value:function(e){e.stopPropagation()}},{key:"render",value:function(){
var e=this.props,t=e.editing,n=e.value,a=e.className
return t?p.default.createElement("div",{className:m("text-wrapper",a),onClick:this.handleStopPropagation},p.default.createElement("textarea",{ref:this.setElementRef,value:n,onFocus:this.handleFocus,onChange:this.handleChange,onBlur:this.handleBlur,onKeyDown:this.handleKeyDown})):p.default.createElement("span",{className:m("text-no-editing",a)},n)}}]),i}(p.PureComponent);(t.default=v).propTypes={editing:i.default.bool,value:i.default.string,className:i.default.string,onFocus:i.default.func,
onBlur:i.default.func,onChange:i.default.func},v.defaultProps={onFocus:function(){},onChange:function(){}}},d89S:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("MVZn")),i=n("/MKj"),b=a(n("J2m7")),o=a(n("KHYK")),l=(0,i.connect)(function(e){return(0,r.default)({},function(e){var t,n,a,r=e.container,i=r.layers,o=i.resourceByScreen,l=i.visibilityScreenID,s=i.activeLayerID,c=i.enteredLayerID,u=r.previewSetting,d=u.ratio,f=u.unit,p=e.model,h=p.current.screenCid,m=p.screens,v=o[l],g=!1,y=f
return v&&(t=(0,b.default)(v.layers,function(e){return e.id===s}),n=(0,b.default)(v.layers,function(e){return e.id===c}),t&&n&&n.id!==t.id&&(g=!0,a=m.find(function(e){return e.cid===h}))),{show:g,ratio:d,distanceUnit:y,selectedLayer:t,hoveringLayer:n,screen:a}}(e))})(o.default)
t.default=l},dAiO:function(e,t,n){},"dYO+":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var d=r(n("J4zp")),i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("17x9")),f=a(n("q1tI")),p=n("Gbs1"),h=r(n("An9T")),m=function(e){function t(){return(0,i.default)(this,t),(0,l.default)(this,(0,s.default)(t).apply(this,arguments))}return(0,c.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.project,n=e.shellType,a=function(e,t,n){switch(e){case"device":var a=(0,p.getProjectShell)(t,e)
if(!a.bg)return null
var r=n?"".concat(a.bg,"_land"):a.bg,i=n?[-a.left,-a.top,a.height,a.width]:[-a.top,-a.left,a.width,a.height],o=(0,d.default)(i,4),l=o[0],s=o[1],c=o[2],u=o[3]
return{top:l,left:s,width:c,height:u,backgroundImage:"url(".concat(MB.isHTMLZip()?".":"","/images/devices/").concat(r,".png)")}
case"default":case"none":return null}}(n,t,e.isLandscape),r="device"===n&&null===a?"none":n
return f.default.createElement("div",{className:"".concat(h.default.shell," ").concat(r),style:a})}}]),t}(f.PureComponent);(t.default=m).propTypes={project:u.default.object,shellType:u.default.string,isLandscape:u.default.bool}},dZ9F:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var c=a(n("q1tI")),r=a(n("17x9")),i=a(n("vOnD")),u=n("/5+U"),o=function(e){var t=e.value,n=e.ratio,a=e.valueRatio,r=e.unit,i=e.style,o=e.className,l=e.customClassName,s=(0,u.adapterScreen)(t,n)
return c.default.createElement("div",{style:i,className:"".concat(o," ").concat(l)},"".concat(Math.round(s*a)).concat(r))},l=(0,i.default)(o).withConfig({displayName:"MarkLabel__StyledMarkValue",componentId:"sc-1b6nimd-0"})(["padding:0 5px;color:#fff;background-color:#ff7100;border-radius:2px;"])
o.propTypes={value:r.default.oneOfType([r.default.string,r.default.number]),ratio:r.default.number,valueRatio:r.default.number,unit:r.default.string,style:r.default.object,className:r.default.string,customClassName:r.default.string}
var s=l
t.default=s},dhJN:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("43RC")),m=r(n("6gQ3")),v=r(n("zgSj")),g=n("oose"),y=n("1iCU"),b=n("fcSx"),S=function(e){function t(e){var n
return(0,i.default)(this,t),n=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(n),"toggleMinimized",function(e){var t=n.props.toolbarActiveItem
n.setState({isMinimized:e}),MB.event("preview","".concat(y.TOOLBAR_TRAKING_CONFIG[t],",点击了").concat(e?"收起":"展开","列表"))}),n.state={isMinimized:MB.isUIChina()||MB.isForum()},n}return(0,u.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.isLayerPanelShow,n=e.isCommentPanelShow,a=e.isScreenPanelShow,r=this.state.isMinimized
if(!(t||n||a))return null
var i=a?240:260
return p.default.createElement(b.StyledLeftPane,{id:"mb-preview-leftpane",style:{width:r?0:i}},a&&p.default.createElement(p.default.Fragment,null,p.default.createElement("div",{className:"preview-panel-wrapper"},p.default.createElement(m.default,null)),p.default.createElement(h.default,{placement:"right",isMinimized:r,onClick:this.toggleMinimized})),t&&p.default.createElement(v.default,null),n&&p.default.createElement(g.CommentContainer,null))}}]),t}(p.PureComponent)
t.default=S,(0,d.default)(S,"propTypes",{toolbarActiveItem:f.default.string,isScreenPanelShow:f.default.bool,isLayerPanelShow:f.default.bool,isCommentPanelShow:f.default.bool})},dppN:function(e,t,n){},eNKG:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.visibilityScreenID=o,t.resourceByScreen=s,t.default=void 0
var r=a(n("lSNA")),i=n("JfQ8")
function o(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:"-1",t=1<arguments.length?arguments[1]:void 0
switch(t.type){case i.SET_VISIBILITY_SCREEN:return t.payload.screenID
default:return e}}var l={"-1":{isFetching:!1,layers:[],error:""}}
function s(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:l,t=1<arguments.length?arguments[1]:void 0
switch(t.type){case i.RECEIVE_RESOURCE_SUCCESS:case i.RECEIVE_RESOURCE_ERROR:return Object.assign({},e,(0,r.default)({},t.payload.screenID,function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:{isFetching:!1,layers:[],error:""},t=1<arguments.length?arguments[1]:void 0
switch(t.type){case i.RECEIVE_RESOURCE_SUCCESS:return Object.assign({},e,{isFetching:!1,layers:t.payload.layers,error:void 0,artboard:t.payload.artboard,documentColor:t.payload.document_colors,globalColor:t.payload.global_colors,globalText:t.payload.text_styles})
case i.RECEIVE_RESOURCE_ERROR:return Object.assign({},e,{isFetching:!1,layers:[],error:t.payload.error})
default:return e}}(e[t.payload],t)))
case"container:layers:clear":return l
default:return e}}var c={visibilityScreenID:o,resourceByScreen:s}
t.default=c},ee4a:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("Kkl0"),r=n("JfQ8")
var i={selectedLayerID:function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:-1,t=1<arguments.length?arguments[1]:void 0
switch(t.type){case a.SELECT_LAYER:return t.payload.layerID===e?-1:t.payload.layerID
case r.SET_VISIBILITY_SCREEN:return-1
default:return e}},activeLayerID:function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:-1,t=1<arguments.length?arguments[1]:void 0
switch(t.type){case a.ACTIVATE_LAYER:return t.payload.layerID
case r.SET_VISIBILITY_SCREEN:return-1
default:return e}},enteredLayerID:function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:-1,t=1<arguments.length?arguments[1]:void 0
switch(t.type){case a.ENTER_LAYER:return t.payload.layerID
default:return e}}}
t.default=i},f7BV:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=function(){function e(){(0,r.default)(this,e),this.timeoutMap=new Map}return(0,i.default)(e,[{key:"setTimeout",value:function(a){function e(e,t,n){return a.apply(this,arguments)}return e.toString=function(){return a.toString()},e}(function(e,t,n){var a=this,r=setTimeout(function(){t(),a.clearTimeout(e,t)},n)
return this.setToken(e,t,r),r})},{key:"clearTimeout",value:function(n){function e(e,t){return n.apply(this,arguments)}return e.toString=function(){return n.toString()},e}(function(e,t){var n=this.getToken(e,t)
void 0!==n&&(clearTimeout(n),this.clearToken(e,t))})},{key:"clearTimeoutByKey",value:function(n){var a=this,e=this.timeoutMap.get(n)
void 0!==e&&(e.forEach(function(e,t){return a.clearTimeout(n,t)}),this.timeoutMap.delete(n))}},{key:"clear",value:function(){var n=this
this.timeoutMap.forEach(function(e,t){return n.clearTimeoutByKey(t)})}},{key:"setToken",value:function(e,t,n){var a=this.timeoutMap.get(e)
void 0===a&&(a=new Map,this.timeoutMap.set(e,a)),a.set(t,n)}},{key:"getToken",value:function(e,t){var n=this.timeoutMap.get(e)
if(n)return n.get(t)}},{key:"clearToken",value:function(e,t){var n=this.timeoutMap.get(e)
n&&n.delete(t)}}]),e}()
t.default=o},fSKh:function(e,t,n){},fcSx:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledLeftPane=void 0
var r=a(n("vOnD")).default.div.withConfig({displayName:"styles__StyledLeftPane",componentId:"uzp97l-0"})(["position:relative;height:100%;transition:all 0.3s ease-in-out;z-index:100;.preview-panel-wrapper{position:absolute;top:0;right:0;height:100%;}"])
t.StyledLeftPane=r},fiFu:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.getUserAuthStatus=t.USER_AUTH_STATUS_MEMBER=t.USER_AUTH_STATUS_NOT_MEMBER=t.USER_AUTH_STATUS_NOT_SIGN_IN=t.getCommentPermission=t.muteEvent=t.MUTE_EVENT=void 0
var a=function(e){e&&e.preventDefault(),e&&e.stopPropagation()}
t.MUTE_EVENT=a
t.muteEvent=function(t){return function(e){return a(e),t&&t(e)}}
var i=[0,1,2,3,4,5,6,7].map(function(e){return{create:!!(1&e),update:!!(2&e),delete:!!(4&e)}})
t.getCommentPermission=function(e,t){var n=2<arguments.length&&void 0!==arguments[2]?arguments[2]:"INVALID_ID_0",a=3<arguments.length&&void 0!==arguments[3]?arguments[3]:"INVALID_ID_1",r=e&&a===n
return i[(e?1:0)+(r?2:0)+(r||t?4:0)]}
var r="NOT_SIGN_IN"
t.USER_AUTH_STATUS_NOT_SIGN_IN=r
var o="NOT_MEMBER"
t.USER_AUTH_STATUS_NOT_MEMBER=o
t.USER_AUTH_STATUS_MEMBER="MEMBER"
t.getUserAuthStatus=function(t){var e=1<arguments.length&&void 0!==arguments[1]?arguments[1]:[]
return(t=t&&String(t))?e.some(function(e){return e.user_id===t})?"MEMBER":o:r}},flWF:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("WVP6"),r=n("Ehhz").MODEL_OPERATION_MAP.Widget,i=(0,a.createStateStore)([]),o=i.getState,l=i.setState,s=i.wrapEntry,c=function(i,o){return s(function(e,t,n){var a=t.dispatch,r=n&&n.payload
a({type:"reducer:widgets:update",payload:i(e,r,o)})})},u={entryMap:{"widgets:refresh":c(r.refreshStateList,!1),"widgets:add":c(r.addState,!1),"widgets:add-local":c(r.addState,!0),"widgets:update":c(r.updateState,!1),"widgets:update-local":c(r.updateState,!0),"widgets:delete":c(r.deleteState,!1),"widgets:delete-local":c(r.deleteState,!0)},getState:o,setState:l}
t.default=u},foKU:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var l=r(n("pVnL")),s=r(n("QILm")),i=r(n("lwsE")),o=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("PJYZ")),f=r(n("7W2i")),p=r(n("lSNA")),h=r(n("17x9")),m=a(n("q1tI")),v=MB.config.SCALES[0],g=MB.config.SCALES[MB.config.SCALES.length-1],y=function(e){function r(){var e,m;(0,i.default)(this,r)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return m=(0,c.default)(this,(e=(0,u.default)(r)).call.apply(e,[this].concat(n))),(0,p.default)((0,d.default)(m),"setElementRef",function(e){return m.$elem=e}),(0,p.default)((0,d.default)(m),"handleWheel",function(e){e.preventDefault()
var t=m.props,n=t.x,a=t.y,r=t.scale,i=t.isDisabled,o=t.onOffsetChange
if(!i){var l=Math.max(-1,Math.min(e.deltaY,1))
if(e.ctrlKey||e.metaKey){var s=m.$elem.getBoundingClientRect(),c=s.top,u=(s.left+s.right)/2,d=(c+s.bottom)/2,f=r<=100?r-5*l:r-r*l*.05,p=e.pageX-u,h=e.pageY-d
m.handleZoom(f,p,h)}else o(n-e.deltaX,a-e.deltaY)}}),m}return(0,f.default)(r,e),(0,o.default)(r,[{key:"componentDidMount",value:function(){this.$elem.addEventListener("wheel",this.handleWheel,{passive:!1})}},{key:"componentWillUnmount",value:function(){this.$elem.removeEventListener("wheel",this.handleWheel,{passive:!1})}},{key:"handleZoom",value:function(e,t,n){var a=this.props,r=a.x,i=a.y,o=a.scale,l=a.onOffsetChange,s=a.onScaleChange,c=(e=Math.min(Math.max(e,v),g))/o
1!=c&&(l(t+c*(r-t),n+c*(i-n)),s(e))}},{key:"render",value:function(){var e=this.props,t=e.x,n=e.y,a=e.scale,r=e.children,i=(e.onOffsetChange,e.onScaleChange,e.isDisabled),o=(0,s.default)(e,["x","y","scale","children","onOffsetChange","onScaleChange","isDisabled"])
return m.default.createElement("div",(0,l.default)({},o,{ref:this.setElementRef}),r.map(function(e){return"function"==typeof e?e(t,n,a,i):e}))}}]),r}(m.PureComponent)
t.default=y,(0,p.default)(y,"propTypes",{x:h.default.number,y:h.default.number,isDisabled:h.default.bool,scale:h.default.number,children:h.default.array,onScaleChange:h.default.func,onOffsetChange:h.default.func})},gSgL:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.SliceContainer=void 0
var s=r(n("o0o1")),i=r(n("yXPU")),l=r(n("lwsE")),o=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("PJYZ")),f=r(n("7W2i")),p=r(n("lSNA")),h=r(n("17x9")),m=a(n("q1tI")),v=n("/MKj"),g=r(n("sEfC")),y=n("wYtL"),b=r(n("i6OX")),S=n("rbsZ"),w=r(n("prTy")),E=r(n("UbMB")),k=r(n("2s0x")),C=n("/5+U"),x=n("Nu6V"),T=n("upRB"),_=E.default.bind(k.default),M=!1,P=function(e){function r(e){var o;(0,l.default)(this,r),o=(0,c.default)(this,(0,u.default)(r).call(this,e)),(0,p.default)((0,d.default)(o),"handleActiveLayer",
function(e){o.setState({activeLayerId:e})}),(0,p.default)((0,d.default)(o),"downloadSlice",(0,i.default)(s.default.mark(function e(){var t,n,a,r,i
return s.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(t=o.props,n=t.projectCid,a=t.projectName,r=t.isLogin,MB&&MB.currentProject&&!MB.currentProject.limitation.inspectable)return(0,S.openRenewModal)("inspectable"),e.abrupt("return")
e.next=4
break
case 4:if(!0!==o.state.download&&r){e.next=6
break}return e.abrupt("return")
case 6:return o.startLoadSlice(),e.next=9,B(n,a)
case 9:i=e.sent,o.endLoadSlice(i)
case 11:case"end":return e.stop()}},e)}))),(0,p.default)((0,d.default)(o),"startLoadSlice",function(){o.startTime=Date.now(),o.setState({download:!0}),MB.event("preview","点击下载全部切图")}),(0,p.default)((0,d.default)(o),"endLoadSlice",function(e){e&&(MB.event("preview","下载全部切图时长".concat(Date.now()-o.startTime)),o.setState({download:!1}))}),(0,p.default)((0,d.default)(o),"requestLayer",function(e){var t=o.props.dispatch
t({type:"REQUEST_SELECT_LAYER",payload:{layerID:e}}),t({type:"reducer:preview-toolbar:update",payload:{isSelectLayer:!0}})}),M=!1,o.state={download:!1,activeLayerId:null}
var t=o.props,n=t.loading,a=t.dispatch
return n&&a({type:"reducer:slice:init"}),o}return(0,f.default)(r,e),(0,o.default)(r,[{key:"componentWillUnmount",value:function(){var e=this.props,t=e.projectCid,n=e.dispatch,a=this.state.download,r="/api/v2/projects/".concat(t,"/build/slices_zips.json")
a&&(M=!0,n({type:"reducer:preview-toolbar:update",payload:{loadSliceUrl:r}}))}},{key:"render",value:function(){var o=this,e=this.state,t=e.download,l=e.activeLayerId,n=this.props,a=n.slicesMap,r=n.loading,i=n.error,s=n.currentArtboardId,c=n.isLogin
return i||r?m.default.createElement(j,null):0===a.length?m.default.createElement(A,null):m.default.createElement("div",{className:_("slice-container")},a.map(function(e){var t=e.name,n=e.id,a=e.artboard_id,r=e.image,i=e.image_set
return m.default.createElement(I,{key:n,src:r,name:t,currentArtboardId:s,id:n,imageSet:i,artboardId:a,requestLayer:o.requestLayer,activeLayer:o.handleActiveLayer,activeLayerId:l})}),m.default.createElement(N,{onClick:this.downloadSlice,isLoading:t,isLogin:c}))}}]),r}(m.PureComponent)
P.propTypes={slicesMap:h.default.array.isRequired,loading:h.default.bool,error:h.default.bool,currentArtboardId:h.default.string,isLogin:h.default.bool,projectCid:h.default.string,projectName:h.default.string,dispatch:h.default.func}
var I=function(e){function t(){var a
return(0,l.default)(this,t),a=(0,c.default)(this,(0,u.default)(t).call(this)),(0,p.default)((0,d.default)(a),"isIncurrentScreen",function(){return a.props.artboardId===a.props.currentArtboardId}),(0,p.default)((0,d.default)(a),"handleClick",function(){var e=a.props,t=e.id,n=e.requestLayer;(0,e.activeLayer)(t),a.isIncurrentScreen()?n(t):console.warn("Not in current Screen")}),(0,p.default)((0,d.default)(a),"handleOnload",function(){a.setState({imageLoad:!0})}),(0,p.default)((0,d.default)(a),"handleError",
function(){throw new Error("image load fail")}),(0,p.default)((0,d.default)(a),"handleMouseEnter",function(){a.setState({loadSingleSlice:!0})}),(0,p.default)((0,d.default)(a),"handleMouseLeave",function(){a.setState({loadSingleSlice:!1})}),(0,p.default)((0,d.default)(a),"handleSingleDownload",function(e){e.persist(),e.stopPropagation(),MB&&MB.currentProject&&!MB.currentProject.limitation.inspectable?(0,S.openRenewModal)("inspectable"):a.delaySingleDownload()}),a.state={imageLoad:!1,loadSingleSlice:!1},
a.imageRef=function(e){return a.$image=e},a.delaySingleDownload=(0,g.default)(function(){var e=a.props,t=e.imageSet,n=e.name;(0,C.downloadWithATag)({url:t,name:n,type:"zip"}),MB.event("preview","在切图列表中下载单张切图")},500,{leading:!0}),a}return(0,f.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.name,n=e.src,a=e.activeLayerId,r=e.id,i=this.state,o=i.imageLoad,l=i.loadSingleSlice,s=o?"opacity-1":"opacity-0",c={display:o?"block":"none"},u=_("slice-item",{active:a===r})
return m.default.createElement(y.Tooltip,{type:"block",content:{click:this.isIncurrentScreen()?null:I18N.preview_panel.not_incurrent_screen}},m.default.createElement("div",{className:u,onClick:this.handleClick,onMouseEnter:this.handleMouseEnter,onMouseLeave:this.handleMouseLeave},m.default.createElement("div",{className:"slice-item-wrap",style:{background:"url(/images/preview/slice-bg.png) left top",backgroundSize:"cover"}},!o&&m.default.createElement("img",{src:"/images/preview/image-load-gif.gif",
alt:"Loading..."}),m.default.createElement(w.default,{style:c,src:n,alt:t,adjustImage:38,className:"".concat(s),onLoad:this.handleOnload,onError:this.handleError})),m.default.createElement("div",{className:"slice-item-content"},m.default.createElement("span",{className:"slice-item-name textEllipsis"},t),l&&m.default.createElement(b.default,{name:"export",type:"dora",onClick:this.handleSingleDownload}))))}}]),t}(m.PureComponent)
I.propTypes={name:h.default.string,src:h.default.string.isRequired,id:h.default.number.isRequired,imageSet:h.default.string.isRequired,currentArtboardId:h.default.string.isRequired,requestLayer:h.default.func.isRequired,activeLayer:h.default.func,activeLayerId:h.default.number,artboardId:h.default.string.isRequired}
var N=function(e){var t=e.onClick,n=e.isLoading,a=e.isLogin?null:I18N.preview.guide_login
return m.default.createElement(y.Tooltip,{content:{click:a},type:"block",position:"top",arrowed:!1,className:_("download"),onClick:t},I18N.preview_panel.download,n?m.default.createElement(L,null):m.default.createElement(b.default,{type:"dora",name:"export",className:_("icon-download")}))}
N.propTypes={onClick:h.default.func,isLoading:h.default.bool,isLogin:h.default.bool}
var R=function(){return m.default.createElement("div",{className:_("layer-load")},m.default.createElement("span",{className:_("spinner")}))},L=function(){return m.default.createElement("div",{className:_("download-slice-load")},m.default.createElement(R,null))},j=function(){return m.default.createElement("div",{className:_("slice-load-wrap")},m.default.createElement(R,null))},A=function(){return m.default.createElement("div",{className:_("no-slice")},m.default.createElement("img",{
src:"/images/preview/no-slice@2x.png"}),m.default.createElement("span",null,I18N.preview_panel.no_slice),m.default.createElement("span",null,I18N.preview_panel.slice_in_sketch),m.default.createElement("a",{href:window.MBSketchPluginDownloadURL},m.default.createElement("img",{src:"/images/preview/ic_sketch@2x.png",alt:"sketch"}),I18N.preview_panel.download_sketch))},B=function(){var n=(0,i.default)(s.default.mark(function e(t,n){var a,r,i,o,l
return s.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:a=!0,i=1
case 2:if(!a){e.next=22
break}if(M)return e.abrupt("return")
e.next=5
break
case 5:return e.next=7,(0,x.fetchSliceZip)(t)
case 7:if(o=e.sent,l=o.url,"ok"!==o.status){e.next=15
break}a=!1,r=l,e.next=17
break
case 15:return e.next=17,(0,C.setTimeoutAsync)(Math.min(2e3*i++,1e4))
case 17:if(20<i)return(0,C.downloadFail)(),e.abrupt("return",!1)
e.next=20
break
case 20:e.next=2
break
case 22:return(0,C.downloadWithATag)({url:"/".concat(r),name:n,type:"zip"}),e.abrupt("return",!0)
case 24:case"end":return e.stop()}},e)}))
return function(e,t){return n.apply(this,arguments)}}(),D=(0,v.connect)(function(e){var t=e.model,n=t.current.projectCid,a=t.user,r=e.container.slices,i=r.slices,o=r.loading,l=r.error,s=(0,T.getCurrentScreen)(e)
return{slicesMap:i,loading:o,error:l,isLogin:!!a.id,projectCid:n,currentArtboardId:s.artboard_id}})(P)
t.SliceContainer=D},gX9a:function(e,t,n){e.exports={"play-setting-menu":"W0ROskokXK_S7WUlDo7D5"}},gXld:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),h=a(n("q1tI")),m=r(n("TSYQ")),v=n("i6OX"),g=r(n("ctY3")),p=n("6x+O"),y=n("Uu/L"),b=function(e){function t(){var r
return(0,i.default)(this,t),r=(0,l.default)(this,(0,s.default)(t).call(this)),(0,d.default)((0,c.default)(r),"setElementRef",function(e){return r.$elem=e}),(0,d.default)((0,c.default)(r),"handleExpand",function(e){r.props.handleScreenItemActions.handleExpand(e,r.props.screen)}),(0,d.default)((0,c.default)(r),"handleActivate",function(e){r.props.handleScreenItemActions.handleActivate(e,r.props.screen)}),(0,d.default)((0,c.default)(r),"handleDown",function(e){if(0===e.button){var t=r.props,n=t.screen,
a=t.handleScreenItemActions.handleDown
a&&a(e,n,r.$elem)}}),(0,d.default)((0,c.default)(r),"handleNameChange",function(e){var t=r.props,n=t.screen,a=t.handleScreenItemActions.handleNameChange
a&&a(e,n)}),(0,d.default)((0,c.default)(r),"handleEdit",function(){var e=r.props,t=e.screen,n=e.handleScreenItemActions.handleEdit
n&&n(t)}),(0,d.default)((0,c.default)(r),"handleBlur",function(){r.props.handleScreenItemActions.handleBlur(r.props.screen,r.isNewScreen),r.isNewScreen=!1}),r.isNewScreen=!1,r}return(0,u.default)(t,e),(0,o.default)(t,[{key:"componentDidMount",value:function(){if(this.props.isActive&&!(0,p.isVisible)(this.$elem)){var e=document.querySelector(".rn-content-body")
if(!e)return
var t=e.getBoundingClientRect(),n=this.$elem.getBoundingClientRect().bottom
e.scrollTop+=n-t.bottom+20}this.props.isEditing&&(this.isNewScreen=!0)}},{key:"stopPropagation",value:function(e){e.stopPropagation()}},{key:"render",value:function(){var e=this.props,t=e.screen,n=e.depth,a=e.isActive,r=e.isEditing,i=e.showExpander,o=e.renderItem,l=e.collapseKeySet,s=e.isLinked,c=e.hoverCid,u=14*(n+1),d=!l.has(t.cid),f=t.cid===c,p=d?"caret-down":"caret-right"
return h.default.createElement(y.StyledScreenItem,{type:"linkable",ref:this.setElementRef,"data-cid":t.cid,"data-link-target-cid":t.cid,onClick:this.handleActivate,onMouseDown:this.handleDown,onDoubleClick:this.handleEdit,style:{paddingLeft:u},className:(0,m.default)("rn-list-item",{active:a,linked:s,hover:f})},i&&h.default.createElement("a",{className:"expander",onClick:this.handleExpand,onDoubleClick:this.stopPropagation},h.default.createElement("i",{className:"fa fa-"+p})),h.default.createElement("div",{
className:"screen-name"},a?h.default.createElement(v.SVGIcon,{name:"design/screen_file"}):h.default.createElement(v.SVGIcon,{name:"design/file_o"}),h.default.createElement(g.default,{editing:r,className:"editable-span",value:MB.unescape(t.name),onChange:this.handleNameChange,onBlur:this.handleBlur})),!r&&o&&o(t))}}]),t}(h.PureComponent);(t.default=b).propTypes={depth:f.default.number,screen:f.default.object,isActive:f.default.bool,isEditing:f.default.bool,isLinked:f.default.bool,showExpander:f.default.bool,
hoverCid:f.default.string,renderItem:f.default.func,handleScreenItemActions:f.default.shape({handleEdit:f.default.func,handleExpand:f.default.func,handleActivate:f.default.func,handleBlur:f.default.func,handleDown:f.default.func,handleNameChange:f.default.func,setAttr:f.default.func}),collapseKeySet:f.default.object}},gY5R:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var l=a(n("cDf5")),s=a(n("J4zp")),r=["#FF6161","#FF6161"],i=["#FFF","#F2F2F2","#000"],o=["#DEDEE4","#D9D9D9"],c=["#F2F2F2","#fff"],u=["#E8E8E8","#DBDBDB"],d={radioLine:{border:["2px solid #F2F2F2","1px solid #C8CDD0"],bg:["#F2F2F2","#F2F2F2"],border_color:["#F2F2F2","#C8CDD0"],active_bg:["#FFFFFF","#FCFCFC"]},shortCutBoder:{border:["1px solid #c8cdd0","1px solid transparent"]},fixedSlider:{bg:["#d9d9d9","#dbdbdb"]},slider:{bg:["#e7e9ea","#C8CDD0"]},linkback:{color:["#101010","#5B6B73"],border:[
"1px solid transparent","1px solid #d9d9d9"]},palette:{active_color:r,high_light_color:["#298DF8","#298DF8"],hr_color:o,panel_bg:i},toolbar:{height:56,shadow:["1px 0 6px 0 rgba(39, 54, 78, 0.12)","0 0 10px 0 rgba(0, 0, 0, 0.25)"],bg:["#FFF","#EDEDED","#000"],icon_disable_color:["#C8CDD0","#C8CDD0"],project_title_color:["#5B6B73","#5B6B73"],icon_color:["#7d8694","#5B6B73"],hover_icon_color:["#415058","#1F292E"],active_icon_color:["#FF6161","#FF6161"],active_icon_bg:["#F2F2F2","#E8E8E8"],active_icon_border:[
"#E8E8E8","#DBDBDB"]},popups:{bg:i,bc:["#DBDBDB","#DEDEE4","#FFF"],header:{bg:["#F2F3F4","#DBDBDB"],tc:["#415058","#415058","#FFF"],icon_color:["#8D9EA7","#8D9EA7"],line_color:["#EDEDED","#E8E8E8"]},line:{label_color:["#1F292E","#1F292E","#1F292E"]},nav:{bg:i,border_color:o,active_border_color:r,label_color:["#415058","#415058"],label_active_color:["#525E71","#525E71"]},footer:{background:["#fff","#fff"],icon_active_color:r}},panel:{bg:i,export_bar:{bg:["#F5F5F5","#EDEDED"],laber_color_bg:["#fff","#f2f2f2"
],disabled_bg:["#fff","#f7f7f7"],disabled_border_color:["#f7f7f7","#f2f2f2"]},header:{bg:["#F2F3F4","#DBDBDB"]},nav:{active_bg:i,icon_color:["#5B6B73","#5B6B73"],icon_active_color:r}},draggablePanel:{bg:i,header:{bg:["#F2F3F4","#DBDBDB"]},layerItem:{bg:["#DBDBDB","#F2F2F2"]},input:{bg:c,border_color:u,border:["1px solid transparent","1px solid #DBDBDB"]},BorderRadius:{border_color:["#f2f2f3","#c8cdd1"]},CheckBorder:{border_color:["#8d9ea6","#bacdd6"]},NumberInput:{bg:c,border_color:u,disabled_bg:["#F7F7F7",
"#fff"],disabled_border_color:["#F2F2F2","#e8e8e8"]},Select:{bg:c,border_color:u}},viewMode:{bg:["#E1E1E1","#E8E8E8"]},leftpane:{shadow:["0 2px 30px 0 rgba(213, 213, 213, 0.5)"],border_right:["","1px solid #C8CDD0"]},rightpane:{shadow:["0 -2px 30px 0 rgba(39,54,78,0.11)"]},subpanel:{border_top_color:["#dbdbdb","#D9D9D9"]},textarea:{bg:c,border_color:u},sidebar:{bg:i,divider_color:["#C8CDD0","#C8CDD0"],icon_color:["#5B6B73","#5B6B73"],icon_hover_color:["#415058","#415058"],icon_active_color:r,
icon_active_bg:["#F4F5F6","#F4F5F6"],icon_hover_bgcolor:["#f2f2f2","#E8E8E8"],icon_hover_border_color:["#E8E8E8","#DBDBDB"],border_right:["1px solid #DEDEE4","1px solid #C8CDD0"],border_left:["","1px solid #C8CDD0"]},leftnav:{bg:i,nav_icon_hover:["#FCFCFC","#EBEBEB"]},basicWidgets:{bg:i,border_color:["#DEDEE4","#c8cdd0"],icon_color:["#6C6D6E","#6C6D6E"],icon_hover_color:["#f2f2f2","#E8E8E8"],icon_hover_border_color:["#E8E8E8","#DBDBDB"]},ruler:{bgColor:["transparent","transparent"],longfgColor:["#BABBBC",
"#BABBBC"],shortfgColor:["#C8CDD0","#C8CDD0"],fontColor:["#8D9EA7","#8D9EA7"],shadowColor:["#E8E8E8","#E8E8E8"],lineColor:["#EB5648","#EB5648"],borderColor:["#DADADC","#DEDEE4"],cornerActiveColor:["rgb(235, 86, 72, 0.6)","rgb(235, 86, 72, 0.6)"]},screenContainer:{bg:["#F5F5F5","#f9f9f9","#000"]},scrollbar:{track:{bg:["transparent","transparent"]},thumb:{x_bg:["#D2D2D8","#BCBCBC"],y_bg:["#DEDEE4","#BCBCBC"],x_hover_bg:["#BEC3C5"],y_hover_bg:["#C8CDD0"]}},listItem:{tc:["#5B6B73","#415058"],hover:{tc:[
"#298DF8","#298DF8"],bc:["#E8E8E8","#D9D9D9"],bg:["#F7F7F7","#E8E8E8"]},expander_color:["#C8CDD0","#8D9EA7"],action_color:["#8D9EA7","#8D9EA7"],action_hover_color:["#5B6B73","#1F292E"],active:{bg:["#F2F2F2","#FFF"],tc:["#298DF8","#298DF8"],bc:["#EBEBEB","#EBEBEB"]}},thumbnail:{bg:["#F2F2F2","#EBEBEB"],border_color:["#EDEDED","#DBDBDB"]},preferenceBar:{bg:["#F5F5F5","#F9F9F9"],bc:["#E7E9EA","#DBDBDB"]},colorButton:{bg:["#F6F7F8","#FCFCFC"],border_color:["#F2F2F3","#DBDBDB"]},searchBar:{bg:c,border_color:u},
interation:{hover:{border_color:["#1E98EA","#1E98EA"]},active:{border_color:["#1E98EA","#1E98EA"],box_shadow:["0 0 4px 0 rgba(34, 162, 237, 0.66)","0 0 4px 0 rgba(34, 162, 237, 0.66)"]}},noComponentImage:["url('/images/workspace/design/no_component_list_light.png')","url('/images/workspace/design/no_component_list_grey.png')"],carouselSettings:{assetBoxBg:["#f7f7f7","#ebebeb"],addAssetIconFill:["#c8cdd0","#8d9ea7"]},linkSettings:{linkView:{detail_bg:["#f7f7f7","#fff"]},gesture:{bg:["#EBEBEB","#FFF"],
border_color:["#EBEBEB","#FFF"],hover:{border_color:["#298DF8","#298DF8"]},active:{border_color:["#298DF8","#298DF8"]}},linkPanel:{bg:["#f7f7f7","#FFF"],divider:["#FFF","#f7f7f7"]}}},f=function r(e,i){var o={}
return Object.entries(e).forEach(function(e){var t=(0,s.default)(e,2),n=t[0],a=t[1]
Array.isArray(a)?o[n]=a[i]:"object"===(0,l.default)(a)?o[n]=r(a,i):o[n]=a}),o},p={light:f(d,0),grey:f(d,1),dark:f(d,2)}
t.default=p},h0FN:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.TIMER_DURATION_LIST=t.ANI_DURATION_LIST=t.TEMPLATE_TRANSITIONS=t.TRANSITIONS=void 0
var a=["leftmenu","rightmenu","leftdrawer","rightdrawer","slideright","slideleft","slidetop","slidebottom","slideleft2","slideright2","topin","popin","leftout","rightout","topout","popout"].map(function(e){return{value:e,label:I18N.tr[e]}}),r=(t.TRANSITIONS=a).filter(function(e){var t=e.value
return!/drawer|menu/.test(t)})
t.TEMPLATE_TRANSITIONS=r
t.ANI_DURATION_LIST=[{label:"0ms",value:"0ms"},"100ms","200ms","300ms","400ms","500ms","750ms","1000ms","2000ms","3000ms","4000ms","5000ms","6000ms","7000ms","8000ms","9000ms","10000ms"]
t.TIMER_DURATION_LIST=["100ms","200ms","300ms","400ms","500ms","750ms","1000ms","2000ms","3000ms","4000ms","5000ms","6000ms","7000ms","8000ms","9000ms","10000ms"]},h2Vm:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var l=r(n("lwsE")),i=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),o=r(n("17x9")),h=r(n("TSYQ")),m=a(n("i6OX")),v=r(n("81q6")),g=r(n("UUBB")),y=r(n("tfo6")),b=r(n("Mn07")),S=r(n("sEfC")),w=n("Hlt7"),E=n("1iCU"),k=n("pVAx"),C=r(n("naIL")),x=[{label:p.default.createElement(m.SVGIcon,{name:"design/list"}),value:"literal"},{label:p.default.createElement(m.SVGIcon,{name:"design/thumbnail"}),value:"thumbnail"}],T=function(e){function o(e){var i;(0,l.default
)(this,o),i=(0,s.default)(this,(0,c.default)(o).call(this,e)),(0,f.default)((0,u.default)(i),"setElementRef",function(e){return i.$elem=e}),(0,f.default)((0,u.default)(i),"handTooltip",function(){$(i.$elem).tooltip({container:"body",selector:".rn-list-item, .thumbnail-item",placement:function(e,t){var n=i.state.viewMode,a=i.props.layout
if(a!==k.RECOMMEND&&a!==k.BETA||"literal"!==n){if("thumbnail"!==n)return"left"
var r=t.getBoundingClientRect()
return r.y+r.height+44>window.innerHeight?"right":"bottom"}return"right"},trigger:"hover",title:function(){var e=this.querySelector(".editable-span"),t=e.offsetWidth,n=e.scrollWidth,a=e.textContent
return t<n&&[a]}})}),(0,f.default)((0,u.default)(i),"handleSearch",function(e){i.debounceSearch(e.toLowerCase()),i.setState({keyword:e})}),(0,f.default)((0,u.default)(i),"debounceSearch",(0,S.default)(function(e){MB.event("preview","使用了页面搜索"),i.props.dispatch({type:"reducer:preview-panel:search",payload:{screenSearch:e}})},300)),(0,f.default)((0,u.default)(i),"handleViewChange",function(e){"literal"===e?i.handleListView():i.handleThumbnail()}),(0,f.default)((0,u.default)(i),"handleListView",function(){
var e=i.props.toolbarActiveItem
MB.event("preview","在".concat(E.TOOLBAR_TRAKING_CONFIG[e],",点击了列表")),i.setState({viewMode:"literal"})}),(0,f.default)((0,u.default)(i),"handleThumbnail",function(){var e=i.props.toolbarActiveItem
MB.event("preview","在".concat(E.TOOLBAR_TRAKING_CONFIG[e],",点击了缩略图")),i.setState({viewMode:"thumbnail"})}),(0,f.default)((0,u.default)(i),"renderCommentIcon",function(e){var t=i.props.screenCommentThreadCountMap
if(1<=(t&&t[e.cid]||0)&&!MB.isHTMLZip())return p.default.createElement("span",{className:"toggle-comment"},p.default.createElement(m.default,{type:"dora",name:"comment"}))})
var t=e.screenTreeData,n=t.nodeMap,a=t.screenNameCidMap,r=e.screenSearch
return i.state={keyword:"",viewMode:e.isDemo?"thumbnail":"literal",searchScreenKeyMap:(0,w.filterSearch)(a,r,n)||[]},i}return(0,d.default)(o,e),(0,i.default)(o,[{key:"UNSAFE_componentWillReceiveProps",value:function(e){var t=e.screenSearch,n=this.props,a=n.screenTreeData,r=a.nodeMap,i=a.screenNameCidMap
if(t!=n.screenSearch){var o=(0,w.filterSearch)(i,t,r)||[]
this.setState({searchScreenKeyMap:o})}}},{key:"componentDidMount",value:function(){this.handTooltip()}},{key:"render",value:function(){var e=this.props,t=e.screenTreeData,n=e.currentScreenCid,a=e.screenSearch,r=e.dispatch,i=this.state,o=i.viewMode,l=i.keyword,s=i.searchScreenKeyMap,c=0<a.length,u=c?{root:s}:t.childListMap
return p.default.createElement("div",{className:C.default["screen-panel"]},p.default.createElement("div",{className:"screen-actions"},p.default.createElement(v.default,{value:l,placeholder:I18N.preview.search,onChange:this.handleSearch}),p.default.createElement(g.default,{className:"viewmode",options:x,value:o,handleChange:this.handleViewChange})),p.default.createElement("div",{className:(0,h.default)("screen-list-container",o),ref:this.setElementRef},"literal"===o?p.default.createElement(y.default,{
activeCid:n,isSearching:c,screenTreeData:t,screenTreeMap:u,screenDataMap:t.nodeMap,renderCommentIcon:this.renderCommentIcon,dispatch:r}):p.default.createElement(b.default,{activeCid:n,screenTreeMap:u,screenDataMap:t.nodeMap,renderCommentIcon:this.renderCommentIcon,dispatch:r})))}}]),o}(p.PureComponent)
t.default=T,(0,f.default)(T,"propTypes",{screenTreeData:o.default.object,screenCommentThreadCountMap:o.default.object,currentScreenCid:o.default.string,screenSearch:o.default.string,toolbarActiveItem:o.default.string,layout:o.default.string,isDemo:o.default.bool,dispatch:o.default.func})},iKZC:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.doSaveWithSocketAndFallback=t.createAutoSaveQueue=void 0
var b=a(n("o0o1")),S=a(n("MVZn")),w=a(n("yXPU")),E=n("xV1f"),k=n("hGv0"),C=n("os03"),x=n("Clcl")
t.createAutoSaveQueue=function(e){var t=e.doSave,n=e.onError,a=e.delay,r=(0,k.createEventTarget)(),i=r.clear,o=r.addEventListener,l=r.removeEventListener,s=r.dispatchEvent,c=(0,C.createSaveQueue)({beforeSave:function(){return s({type:"beforesave"})},afterSave:function(){return s({type:"aftersave"})},doSave:t,onError:n}),u=c.clear,d=c.add,f=c.save,p=c.filter,h=c.getLength,m=c.getIsSaving,v=c.getSavingState,g=(0,E.createTimer)({func:f,delay:a}),y=g.start,b=g.stop,S=g.getDelay,w=g.setDelay
return{reset:function(){b(),i(),u()},add:function(e){d(e),y()},getState:function(){return{pendingLength:h(),isSaving:m(),delay:S(),savingState:v()}},getIsEmpty:function(){return!m()&&!h()},getIsSaving:m,getDelay:S,setDelay:w,filterSaveQueue:p,triggerSave:f,afterCurrentSave:function(t){if(!m())return t()
o("aftersave",function e(){l("aftersave",e),t()})},addEventListener:o,removeEventListener:l}}
var r=function(){var t=(0,w.default)(b.default.mark(function e(t){var c,u,n,d,f,p,h,m,v,g,y,a,r,i
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:c=t.setSavingState,u=t.getAutoSaveQueueState,n=t.saveChunkList,d=t.saveQueueLength,f=t.getSaveItemInfo,p=t.isSocketAvailable,h=t.doSocketBatchSave,m=t.onSocketError,v=t.doFallbackSaveItem,g=t.onFallbackError,y=0,a=b.default.mark(function e(r,i){var s,o,t
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:s=n[r],o=0,t=b.default.mark(function e(){var l,t,n,a
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(l={chunkIndex:r,chunkIndexMax:i,saveChunkFirstInfo:f(s[0]),saveChunkLength:s.length,chunkAttempt:o,saveQueueIndex:y,saveQueueLength:d},e.prev=1,p())return e.next=5,(0,C.withTimeoutRetry)({retry:2,timeout:6e4,task:function(){var t=(0,w.default)(b.default.mark(function e(t){var n,a
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.attempt,a=t.timeout,c((0,S.default)({type:"socket-batch-save",attempt:n,timeout:a},l)),e.next=4,h({saveChunk:s,attempt:n,timeout:a})
case 4:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}(),onError:function(){var n=(0,w.default)(b.default.mark(function e(t,n){var a,r
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return a=n.attempt,r=n.timeout,c((0,S.default)({type:"socket-batch-save-retry",error:t.toString(),attempt:a,timeout:r},l)),e.next=4,m(t,{saveChunk:s,attempt:a,timeout:r})
case 4:case"end":return e.stop()}},e)}))
return function(e,t){return n.apply(this,arguments)}}()})
e.next=6
break
case 5:return e.abrupt("return","break")
case 6:e.next=11
break
case 8:e.prev=8,e.t0=e.catch(1),(0,x.REPORT_ERROR)(e.t0,"[AutoSaveQueue][doSave] failed to save with socket",u())
case 11:e.prev=11,t=b.default.mark(function e(t,n){var i,o
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return i=s[t],o=(0,S.default)({index:t,indexMax:n,saveItem:f(i)},l,{saveQueueIndex:y+t}),e.next=4,(0,C.withTimeoutRetry)({retry:4,timeout:1e5,task:function(){var t=(0,w.default)(b.default.mark(function e(t){var n,a
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=t.attempt,a=t.timeout,c((0,S.default)({type:"fallback-save-item",attempt:n,timeout:a},o)),e.next=4,v({saveItem:i,attempt:n,timeout:a})
case 4:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}(),onError:function(){var n=(0,w.default)(b.default.mark(function e(t,n){var a,r
return b.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return a=n.attempt,r=n.timeout,c((0,S.default)({type:"fallback-save-item-retry",error:t.toString(),attempt:a,timeout:r},o)),e.next=4,g(t,{saveItem:i,attempt:a,timeout:r})
case 4:case"end":return e.stop()}},e)}))
return function(e,t){return n.apply(this,arguments)}}()})
case 4:case"end":return e.stop()}},e)}),n=0,a=s.length
case 14:if(n<a)return e.delegateYield(t(n,a),"t1",16)
e.next=19
break
case 16:n++,e.next=14
break
case 19:return e.abrupt("return","break")
case 22:e.prev=22,e.t2=e.catch(11),(0,x.REPORT_ERROR)(e.t2,"[AutoSaveQueue][doSave] failed to save with fetch fallback",u())
case 25:o++
case 26:case"end":return e.stop()}},e,null,[[1,8],[11,22]])})
case 3:return e.delegateYield(t(),"t0",5)
case 5:if("break"===e.t0)return e.abrupt("break",10)
e.next=8
break
case 8:e.next=3
break
case 10:y+=s.length
case 11:case"end":return e.stop()}},e)}),r=0,i=n.length
case 4:if(r<i)return e.delegateYield(a(r,i),"t0",6)
e.next=9
break
case 6:r++,e.next=4
break
case 9:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.doSaveWithSocketAndFallback=r},iLpg:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledSearchBar=void 0
var r=a(n("vOnD")),i=n("+IKJ"),o=r.default.div.withConfig({displayName:"styles__StyledSearchBar",componentId:"jsl19y-0"})(["position:relative;height:24px;display:flex;justify-content:space-between;align-items:center;.search-icon{position:absolute;left:0;width:24px;height:24px;text-align:center;line-height:24px;font-size:12px;color:#8d9ea7;pointer-events:none;}input{width:100%;height:100%;padding-right:22px;background:",";border:1px solid ",";border-radius:2px;transition:all 0.2s ease-out;",
";text-indent:24px;&:hover{border-color:",";}&:focus{background:#fff;border-color:",";box-shadow:",";}}.clear-icon{position:absolute;right:0;width:24px;line-height:24px;text-align:center;color:#bec2c9;transition:all 0.15s ease-in-out;cursor:pointer;&:hover{color:#7d8695;}}"],function(e){return e.theme.searchBar.bg},function(e){return e.theme.searchBar.border_color},(0,i.placeholder)({color:"#8d9ea7"}),function(e){return e.theme.interation.hover.border_color},function(e){
return e.theme.interation.active.border_color},function(e){return e.theme.interation.active.box_shadow})
t.StyledSearchBar=o},iScx:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("WVP6"),i=n("Ehhz").MODEL_OPERATION_MAP.Collaborator,r=(0,a.createStateStore)([]),o=r.getState,l=r.setState,s=r.wrapEntry,c=function(i,o){return s(function(e,t,n){var a=t.dispatch,r=n&&n.payload
a({type:"reducer:collaborators:update",payload:i(e,r,o)})})},u={entryMap:{"collaborators:refresh":s(function(e,t,n){var a=t.dispatch,r=n&&n.payload;(e=i.refreshStateList(e,r,!1)).forEach(function(e){e.avatar||(e.avatar="/images/avatar.png")}),a({type:"reducer:collaborators:update",payload:e})}),"collaborators:add":c(i.addState,!1),"collaborators:add-local":c(i.addState,!0),"collaborators:update":c(i.updateState,!1),"collaborators:update-local":c(i.updateState,!0),"collaborators:delete":c(i.deleteState,!1),
"collaborators:delete-local":c(i.deleteState,!0)},getState:o,setState:l}
t.default=u},iX79:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=n("i6OX"),m=n("wYtL"),v=r(n("RtVw")),g=n("/5+U"),y=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"handleFullScreen",function(){MB.event("zhuge",(0,g.canBackToWorkspace)()?"Preview_enter_FullScreen":"LinkPreview_enter_FullScreen"),t.props.dispatch({type:"entry:enter:full-screen-mode"})}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){return p.default.createElement(m.Tooltip,{position:"bottom",tipClassName:"margin-top-20",duration:1e3,content:I18N.preview.fullscreen,
style:{lineHeight:0,cursor:"pointer"}},p.default.createElement("div",{className:v.default.fullscreen,onClick:this.handleFullScreen},p.default.createElement(h.SVGIcon,{name:"design/fullscreen"})))}}]),i}(p.PureComponent)
t.default=y,(0,f.default)(y,"propTypes",{dispatch:i.default.func})},ibfc:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var f=r(n("MVZn")),o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),p=r(n("lSNA")),i=r(n("17x9")),h=a(n("q1tI")),m=r(n("9DAG")),v=n("MGhH"),g=r(n("WtCM")),y=r(n("TSYQ"))
n("aw2M")
var b=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,p.default)((0,u.default)(t),"setScreenRef",function(e){return t.$screen=e}),(0,p.default)((0,u.default)(t),"getScreenElement",function(){return t.$screen}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"componentWillUnmount",value:function(){var e=this.props.screen
MB.runner.runnerUtil.destroyScrollBarByCid(e.cid)}},{key:"render",value:function(){var e=this.props,t=e.isShow,n=e.screen,a=e.isActive,r=e.style,i=e.widgetQueryMap,o=n.cid,l=n.stateCid,s=n.transition,c=Screen.find(n.cid),u=(0,f.default)({display:t?"":"none",backgroundColor:c.bg(),backgroundImage:c.bgimage?"url(".concat(c.bgimage,")"):""},r),d=(0,y.default)("pcanvas",c.orient(),{active:a})
return h.default.createElement("div",{ref:this.setScreenRef,id:"pscreen".concat(c.cid),"data-cid":c.cid,"data-orientation":c.orient(),className:d,style:u},h.default.createElement(S,{screenCid:o,stateCid:l,transition:s,widgetQueryMap:i,getScreenElement:this.getScreenElement}))}}]),i}(h.PureComponent)
t.default=b,(0,p.default)(b,"propTypes",{isShow:i.default.bool,screen:i.default.object,isActive:i.default.bool,style:i.default.object,widgetQueryMap:i.default.object})
var S=function(e){function t(){return(0,o.default)(this,t),(0,s.default)(this,(0,c.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,l.default)(t,[{key:"render",value:function(){var e=this.props,t=e.screenCid,n=e.stateCid,a=e.transition,r=e.widgetQueryMap,i=e.getScreenElement,o=Screen.find(t),l=o.headerHeight(),s=o.footerHeight(),c={height:o.height-(l+s)},u={height:o.height,marginTop:-l}
return h.default.createElement(g.default,{screenCid:t,stateCid:n,transition:a,widgetQueryMap:r,getScreenElement:i},function(e){return h.default.createElement(h.default.Fragment,null,h.default.createElement("div",{className:"screen-header",style:{height:l}},0<l&&h.default.createElement(w,{treeData:e,headerHeight:l})),h.default.createElement("div",{className:"screen-content"},h.default.createElement("div",{className:"widgets",style:c},h.default.createElement("div",{className:"scontainer",style:u},
h.default.createElement(m.default,{widgetTreeData:e})))),h.default.createElement("div",{className:"screen-footer",style:{height:s}},0<s&&h.default.createElement(E,{treeData:e,footerHeight:s,screenHeight:o.height})))})}}]),t}(h.PureComponent);(0,p.default)(S,"propTypes",{screenCid:i.default.string,stateCid:i.default.string,transition:i.default.object,widgetQueryMap:i.default.object,getScreenElement:i.default.func})
var w=function(e){var t=e.treeData,n=e.headerHeight,a=(0,v.headerFilter)(t,n)
return h.default.createElement(m.default,{widgetTreeData:a})}
w.propTypes={treeData:i.default.object,headerHeight:i.default.number}
var E=function(e){var t=e.treeData,n=e.footerHeight,a=e.screenHeight,r=(0,v.footerFilter)(t,a,n)
return h.default.createElement("div",{className:"footer-widgets",style:{marginTop:n-a}},h.default.createElement(m.default,{widgetTreeData:r}))}
E.propTypes={treeData:i.default.object,footerHeight:i.default.number,screenHeight:i.default.number}},ibhU:function(e,t,n){e.exports={"runner-state-panel":"_2fELsPyTr6Bvb5x4zc4dSg"}},inTe:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var Re=a(n("MVZn")),r=a(n("17x9")),Le=a(n("q1tI")),je=n("qOCw"),Ae=n("Ro3d"),Be=n("PqLM"),De=n("RUem"),i=function(e){var t=e.layer,n=e.unit,a=e.ratio,r=e.showGlobal,i=e.userPickColor,o=void 0===i?[]:i,l=e.globalColor,s=void 0===l?[]:l,c=e.globalText,u=void 0===c?[]:c,d=e.documentColor,f=void 0===d?[]:d,p=e.screenColor,h=void 0===p?[]:p,m=e.language,v=e.colorUnit,g=e.dispatch,y=t.src_left,b=t.src_top,S=t.src_width,w=t.src_height,E=t.origin_width,k=t.origin_height,C=t.bd_radius,x=t.line_height,T=t.bg_colors,
_=void 0===T?[]:T,M=t.borders,P=void 0===M?[]:M,I=t.i,N=t.display_name,R=t.padding,L=void 0===R?0:R,j=t.hiddSpacing,A=void 0!==j&&j,B=t.text_styles,D=void 0===B?[]:B,O=t.alignment,F=t.vertical_alignment,q=t.image,W=t.text,U=t.letter_spacing,z=t.image_set_zip,Y=t.shadows,H=void 0===Y?[]:Y,V=t.inner_shadows,X=void 0===V?[]:V,J=t.rotation,Z=t.textShadows,K=void 0===Z?[]:Z,G=t.image_set,Q=void 0===G?[]:G,$=t.name,ee=0<P.length,te=0<_.length,ne=!!q,ae=0<D.length&&W&&(0,je.getTextContent)(t).length,
re=0<H.length||0<K.length,ie=0<X.length,oe=z,le={left:y,top:b,width:E||S,height:k||w,borderRadius:C,opacity:t.o,rotation:J,ratio:a,unit:n}
if("line"===$){var se=(0,Be.getLineGeneralInfo)(t,!0),ce=se.length,ue=se.thickness,de=se.angle
le.width=ce,le.height=ue,le.rotation=de}var fe=(0,je.getBaseAttributes)(le),pe=fe.adapterTop,he=fe.adapterLeft,me=fe.adapterWidth,ve=fe.adapterHeight,ge=fe.radius,ye=fe.opacity,be=fe.rotate,Se={lineHeight:x,letterSpacing:U,unit:n,ratio:a},we=(0,je.getTextAttributes)(Se),Ee=we.lineHeight,ke=we.letterSpacing,Ce="number"==typeof I?I?"italic":"normal":void 0,xe={textStyles:D,background:_,borders:P,shadows:H,innerShadows:X,colorUnit:v,ratio:a,unit:n},Te=(0,je.getCodeAttributes)(xe),_e=t.o&&100!=t.o?t.o/100:null,
Me=(0,Ae.transfromProptype)({attr:(0,Re.default)({x:he,y:pe,width:me,height:ve,lineHeight:Ee,textAlign:O,opacity:_e,borderRadius:ge},Te),language:m,unit:n}),Pe=ne?"ImageView":ae?"TextView":"View",Ie="screen"===t.type||t.kind?t.name:N,Ne="line"===t.name
return r?Le.default.createElement(Le.default.Fragment,null,Le.default.createElement(De.LayerName,{title:I18N.preview_panel.screen_name,value:Ie}),Le.default.createElement(De.GlobalAttributes,{adapterWidth:me,adapterHeight:ve,documentColor:f,globalText:u,globalColor:s,screenColor:h,userPickColor:o,colorUnit:v,dispatch:g})):Le.default.createElement("div",null,Le.default.createElement(De.LayerName,{value:Ie}),Le.default.createElement(De.BasicAttributes,{adapterTop:pe,adapterLeft:he,adapterWidth:me,
adapterHeight:ve,rotate:be,radius:ge,opacity:ye,unit:n,colorUnit:v}),ae&&Le.default.createElement(De.TextLayerInfo,{textStyles:D,alignment:O,vertical_alignment:F,lineHeight:Ee,letterSpacing:ke,ratio:a,unit:n,o:t.o,padding:L,fontStyle:Ce,colorUnit:v,hiddSpacing:A,text:(0,je.getTextContent)(t)}),te&&Le.default.createElement(De.Fills,{backgroundColorSort:_,colorUnit:v}),ee&&Le.default.createElement(De.BorderInfo,{isStroke:Ne,borderSort:P,ratio:a,unit:n,colorUnit:v}),re&&Le.default.createElement(De.Shadows,{
shadows:H,textShadows:K,colorUnit:v,unit:n,ratio:a}),ie&&Le.default.createElement(De.Shadows,{shadows:X,colorUnit:v,unit:n,ratio:a,isInnerShaow:!0}),oe&&Le.default.createElement(De.ImageInfo,{imageSetZip:z,name:t.display_name,imageSet:Q}),Le.default.createElement(De.CodeBox,{code:Me,whichAndView:Pe,language:m,text:(0,je.getTextContent)(t)||""}))}
i.propTypes={userPickColor:r.default.array,screenColor:r.default.array,documentColor:r.default.array,globalText:r.default.array,globalColor:r.default.array,colorUnit:r.default.string,layer:r.default.object,getLayerRef:r.default.func,showGlobal:r.default.bool,unit:r.default.string,ratio:r.default.number,language:r.default.string,dispatch:r.default.func}
var o=i
t.default=o},j1JO:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=d,t.watchFetchSlices=f,t.fetchSliceData=p
var o=a(n("MVZn")),l=a(n("o0o1")),s=n("oZtI"),c=a(n("Nu6V")),r=l.default.mark(d),i=l.default.mark(f),u=l.default.mark(p)
function d(){return l.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,s.all)([f()])
case 2:case"end":return e.stop()}},r)}function f(){return l.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,s.takeEvery)("reducer:slice:init",p)
case 2:case"end":return e.stop()}},i)}function p(e){var t,n,a,r,i
return l.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,s.select)()
case 2:if(t=e.sent,n=t.model.current.projectCid,e.prev=4,n)return e.next=8,(0,s.call)(c.default,n)
e.next=14
break
case 8:a=e.sent,r=a.slices,i=r.filter(h),a.slices=i,e.next=15
break
case 14:a={slices:[{id:1,name:"test",screen_cid:"sssss1232",image:"/uploads/images/14/149316/artboard_1506665060.png",src:"ssss",image_set:[{size:1,src:"src"}],image_set_zip:"src"},{id:2,name:"test",screen_cid:"sssss1232",image:"/uploads/images/14/149316/artboard_1506665060.png",image_set:[{size:1,src:"src"}],image_set_zip:"src"},{id:3,name:"test",screen_cid:"sssss1232",image:"/uploads/images/14/149316/artboard_1506665060.png",image_set:[{size:1,src:"src"}],image_set_zip:"src"}]}
case 15:return e.next=17,(0,s.put)({type:"reducer:slice:success",payload:(0,o.default)({},a)})
case 17:e.next=24
break
case 19:return e.prev=19,e.t0=e.catch(4),console.log(e.t0.stack),e.next=24,(0,s.put)({type:"reducer:slice:fail"})
case 24:case"end":return e.stop()}},u,null,[[4,19]])}var h=function(e){var t=e.width,n=void 0===t?1:t,a=e.height
return 0<n&&0<(void 0===a?1:a)}},jZq5:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=n("G4qV"),o=n("upRB"),l=n("1iCU"),s=a(n("K7IS")),c=(0,i.createSelector)([o.getCurrentMode,function(e){return e.container.common.offset}],function(e,t){var n=Boolean(t.x||t.y)
return{isLayerActive:e===l.INSPECT,isDisplaced:n}}),u=(0,r.connect)(function(e){return c(e)})(s.default)
t.default=u},jeLk:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=function(){function e(){(0,r.default)(this,e),this.store=null,this.viewMap={},this.observerMap={}}return(0,i.default)(e,[{key:"setStore",value:function(e){this.store=e}},{key:"callObserver",value:function(e){for(var t,n=arguments.length,a=new Array(1<n?n-1:0),r=1;r<n;r++)a[r-1]=arguments[r]
return this.observerMap[e]&&(t=this.observerMap)[e].apply(t,[e].concat(a))}},{key:"setObserver",value:function(e,t){this.observerMap[e]=t}},{key:"setView",value:function(e,t){this.viewMap[e]=t}},{key:"callViewMethod",value:function(e,t){for(var n,a=this.viewMap[e],r=arguments.length,i=new Array(2<r?r-2:0),o=2;o<r;o++)i[o-2]=arguments[o]
return a&&a[t]?(this.callObserver("view:".concat(e,":").concat(t)),a[t].apply(a,[this.store].concat(i))):(n=console).warn.apply(n,["[WebpackInterface][callViewMethod] missed",e,t].concat(i))}},{key:"init",value:function(){this.callObserver("init"),this.store&&this.store.dispatch({type:"entry:state:init"})}},{key:"clear",value:function(){this.store&&this.store.dispatch({type:"entry:state:clear"}),this.callObserver("clear")}}]),e}()
t.default=o},jvRN:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.getMockingBotWidgets=t.isSketchLayer=t.checkColor=void 0
var m=a(n("MVZn")),u=n("G3NE"),o=a(n("cl8F")),l=n("Ibie"),d=n("FkXu"),y=n("LbTH"),i=n("2EV6"),s=n("/5+U"),c=n("upRB"),b=/\\\w+/gi,S=function(e){return e?e.replace(b,"").trim():o.default}
t.checkColor=S
t.isSketchLayer=function(e){return Number.isInteger(e)||"artboard-base"===e}
t.getMockingBotWidgets=function(e){var t=e.model.widgets,n=(0,c.getCurrentProject)(e).device,a=(0,c.getCurrentScreen)(e),r=f(a.cid),i=t.concat(r),o=0
return i.filter(function(e){return o||e.screen_cid!==a.cid||"status_bar"!==e.name||(o=e.height),!(e.screen_cid!==a.cid||["pg","lr","sticky"].includes(e.name)||"image_view"===e.name&&e.width===a.width&&e.height===a.height)}).map(function(e){return(0,l.patchWidgetSize)(e,a,o)}).map(function(e){return p(e,n)}).sort(function(e,t){return e.z-t.z||e.timestamp-t.timestamp})}
var f=function(p){var e=window.Screen
if(!e)return[]
var t=e.find(p).cpanels(),h=[]
return t.forEach(function(c){h.push(c.__proto__)
var u=c.cid,d=c.top,f=c.left;(c.multi_states?c.ct().homeScreen().cwidgets().map(function(e){return Widgetstate.find(c.main_state_cid+e.cid)||Widgetstate.find("default"+e.cid)||e}):c.mainState().cwidgets()).forEach(function(e){var t=e.top,n=e.left,a=e.width,r=e.height,i=f+Math.min(Math.max(n,0),c.width),o=f+Math.min(Math.max(n+a,0),c.width),l=d+Math.min(Math.max(t,0),c.height),s=d+Math.min(Math.max(t+r,0),c.height)
h.push((0,m.default)({},e.__proto__,{id:"".concat(c.cid,"-").concat(e.id),panel_cid:u,screen_cid:p,top:l,left:i,width:o-i,height:s-l}))})}),h},p=function(e,t){var n,a={},r=e.name,i=e.ro,o=e.border_radius,l=e.bs,s=e.ha,c=e.va,u=e.lh,d=e.box_shadow,f=e.text_shadow,p=e.sc,h=e.ds,m=e.text
if(m&&(n=w(m.replace(/<p>/g,"").replace(/<\/p>/g,"\n")),a.text_styles=(0,y.checkIfItemTextIsNewVersion)(e)?[k(JSON.parse(e.text))]:[{font_size:e.fs,color:S(e.tc||E(r,"tc",t)),length:n.length,font_face:C(m,t)}],a.text=n),s&&(a.alignment=s),c&&(a.vertical_alignment=c),u&&(a.line_height=u),o&&(a.bd_radius=o),i&&(a.rotation=i),a.bc=S(e.bc||E(r,"bc",t)),l&&(a.borders=[{thickness:l,color:S(a.bc)}]),e.bg&&(a.bg_colors=[{value:S(e.bg)}]),"triangleb"!==r&&"triangletl"!==r&&"icon_button"!==r||(a.bg_colors=[{value:S(
e.tc||E(r,"tc"))}]),d){var v=JSON.parse(d)[0]
a.shadows=[{offset_x:v[1],offset_y:v[2],blur_radius:v[3],spread:v[4],color:S(v[5].replace(b,""))}]}else p&&h&&(a.shadows=[{color:S(p.replace(b,"")),blur_radius:h}])
if(f){var g=JSON.parse(f)[0]
a.textShadows=[{offset_x:g[0],offset_y:g[1],blur_radius:g[2],color:S(g[3].replace(b,""))}]}else e.ts&&(a.textShadows=[{color:S(e.tsc.replace(b,"")),blur_radius:e.ts}])
return"label"!==r&&"text_view"!==r||(a.hiddSpacing=!0),Object.assign({},e,a)},r=/<[^>]+>/gi,w=function(e){return!!e&&e.replace(r,"")},E=function(e,t,n){var a="".concat(e,"_").concat(n),r=e,i=o.default[a]||o.default[r]
return i&&i[t]?i[t]:o.default[t]},k=function(e){var t=(0,u.getRichTextAttr)(e),n=t.fontFamily,a=t.fontWeight,r=t.fontSize,i=t.color,o=t.fontStyle,l=t.letterSpacing,s=t.lineHeight,c=t.paraSpacing
return{font_face:"".concat((0,d.getFontFamilyAndWeightText)(n,a)),font_size:r,color:i,fontStyle:o,letterSpacing:l,lineHeight:s,paraSpacing:c}},C=function(e,t){var n=(0,s.isChinese)(e)?"chinese":"english",a=h()?"mac":"windows",r=(0,i.getProjectPlatformByDevice)(t)
return v[a][r][n]},h=function(){return/Mac|iPod|iPhone|iPad/.test(navigator.platform)},v={mac:{ios:{chinese:"PingFang SC",english:"-apple-system"},android:{chinese:"PingFang SC",english:"Roboto"},others:{chinese:"PingFang SC",english:"Roboto"}},windows:{ios:{chinese:"Microsoft Yahei",english:"Arial"},android:{chinese:"Microsoft Yahei",english:"Roboto"},others:{chinese:"Microsoft Yahei",english:"Roboto"}}}},kJQk:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=a(n("8Fba")),o=(0,n("/5+U").immutableTransformCache)(function(e,t){return e.find(function(e){return e.cid===t})}),l=(0,r.connect)(function(e){var t=e.model,n=t.current,a=t.projects,r=o(a,n.projectCid),i=s(r.access_token,n.screenCid)
return{scale:1,width:"100%",height:"100%",src:"".concat(i,"&").concat(Date.now())}})(i.default)
t.default=l
var s=function(e,t){return"".concat("/snapshot.png","?access-token=").concat(e,"&screen-cid=").concat(t,"&mode=zoom-1.00")}},lCKy:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),i=r(n("17x9")),h=n("6XO9"),m=n("wYtL"),v=r(n("i6OX")),g=n("1iCU"),y=r(n("UbMB")),b=r(n("gX9a")),S=y.default.bind(b.default),w=function(e){function r(){var e,i;(0,o.default)(this,r)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return i=(0,s.default)(this,(e=(0,c.default)(r)).call.apply(e,[this].concat(n))),(0,f.default)((0,u.default)(i),"handleClose",function(){var e=i.props,t=e.isScrollable,n=e.isHighlight,a=e.isStickyShow,r=e.shellType
MB.event("zhuge","运行页-预览-收起设置面板",{"内容区滚动":t?"开":"关","链接高亮":n?"开":"关","批注显示":a?"开":"关","边框类型":r})}),i}return(0,d.default)(r,e),(0,l.default)(r,[{key:"render",value:function(){var e=this.props,t=e.canSetDeviceShell,n=e.isScrollable,a=e.isHighlight,r=e.isStickyShow,i=e.shellType,o=e.disabled,l=e.dispatch,s=p.default.createElement(m.Tooltip,{position:"bottom",tipClassName:"marign-top-20",duration:1e3,content:{hover:o?null:I18N.preview.setting}},p.default.createElement(v.default,{name:"cog",type:"dora"}))
return p.default.createElement(h.Dropdown,{disabled:o,menuClassName:S("play-setting-menu"),opener:s,menuX:"right",onClose:this.handleClose,menu:p.default.createElement(E,{canSetDeviceShell:t,isScrollable:n,isHighlight:a,isStickyShow:r,shellType:i,dispatch:l})})}}]),r}(p.PureComponent)
t.default=w,(0,f.default)(w,"propTypes",{canSetDeviceShell:i.default.bool,isScrollable:i.default.bool,isHighlight:i.default.bool,isStickyShow:i.default.bool,shellType:i.default.string,disabled:i.default.bool,dispatch:i.default.func})
var E=function(e){function i(){var e,n;(0,o.default)(this,i)
for(var t=arguments.length,a=new Array(t),r=0;r<t;r++)a[r]=arguments[r]
return n=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(n),"handleToggleScrollable",function(e){n.props.dispatch({type:"entry:preview-setting:update:is-scrollable",payload:{isScrollable:e}})}),(0,f.default)((0,u.default)(n),"handleToggleHighlight",function(e){n.props.dispatch({type:"entry:preview-setting:update:is-highlight",payload:{isHighlight:e}})}),(0,f.default)((0,u.default)(n),"handleToggleSticky",function(e){n.props.dispatch({
type:"entry:preview-setting:update:is-sticky-show",payload:{isStickyShow:e}})}),(0,f.default)((0,u.default)(n),"handleUpdateShellType",function(e){var t=e.value
n.props.dispatch({type:"entry:preview-setting:update:shell-type",payload:{shellType:t}})}),n}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props,t=e.canSetDeviceShell,n=e.isScrollable,a=e.isHighlight,r=e.isStickyShow,i=e.shellType,o=t?g.SHELL_TYPE_LIST:g.SHELL_TYPE_LIST_WITHOUT_DEVICE,l=n?i:"none"
return p.default.createElement(p.default.Fragment,null,p.default.createElement("div",{className:"line"},p.default.createElement("label",null,I18N.content_scrollable),p.default.createElement(h.Switch,{isChecked:n,onChange:this.handleToggleScrollable})),p.default.createElement("div",{className:"line"},p.default.createElement("label",null,I18N.highlight_clickable),p.default.createElement(h.Switch,{isChecked:a,onChange:this.handleToggleHighlight})),p.default.createElement("div",{className:"line"},
p.default.createElement("label",null,I18N.sticky_visible),p.default.createElement(h.Switch,{isChecked:r,onChange:this.handleToggleSticky})),p.default.createElement("div",{className:"line"},p.default.createElement("label",null,I18N.shell_type),p.default.createElement(h.RadioGroup,{size:"small",isDisabled:!n,value:l,optionList:o,onChange:this.handleUpdateShellType})))}}]),i}(p.PureComponent);(0,f.default)(E,"propTypes",{canSetDeviceShell:i.default.bool,isScrollable:i.default.bool,isHighlight:i.default.bool,
isStickyShow:i.default.bool,shellType:i.default.oneOf(["device","default","none"]),dispatch:i.default.func})},ldhK:function(e,t,n){e.exports={covers:"_34w6V_VwmKGjpRAt-ipxe_"}},lwmc:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),d=r(n("17x9")),E=a(n("q1tI")),k=r(n("gXld")),f=n("Uu/L"),p=function(e){function t(){return(0,i.default)(this,t),(0,l.default)(this,(0,s.default)(t).apply(this,arguments))}return(0,c.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,n=e.treeProps,a=e.isSearching,r=e.editingCid,i=e.activeCid,o=e.screenTreeMap,l=e.screenDataMap,s=e.collapseKeySet,c=e.targetlinkCid,u=e.hoverCid
return E.default.createElement(f.StyledScreenList,null,0===o.root.length?E.default.createElement("div",{className:"not-match"},I18N.preview_panel.not_match):o.root.map(function(e){var t=e.cid
return E.default.createElement(h,{key:t,cid:t,depth:0,collapseKeySet:s,isSearching:a,editingCid:r,hoverCid:u,targetlinkCid:c,activeCid:i,screenDataMap:l,screenTreeMap:o,treeProps:n})}))}}]),t}(E.PureComponent)
t.default=p,(0,u.default)(p,"propTypes",{treeProps:d.default.object,isSearching:d.default.bool,editingCid:d.default.string,hoverCid:d.default.string,activeCid:d.default.string,targetlinkCid:d.default.string,screenTreeMap:d.default.object,screenDataMap:d.default.object,collapseKeySet:d.default.object})
var h=function(e){function w(){return(0,i.default)(this,w),(0,l.default)(this,(0,s.default)(w).apply(this,arguments))}return(0,c.default)(w,e),(0,o.default)(w,[{key:"render",value:function(){var e=this.props,t=e.cid,n=e.treeProps,a=e.depth,r=e.activeCid,i=e.editingCid,o=e.isSearching,l=e.screenTreeMap,s=e.screenDataMap,c=e.collapseKeySet,u=e.targetlinkCid,d=e.hoverCid,f=n.renderItem,p=n.handleScreenItemActions,h=s[t],m=!c.has(t),v=l[t],g=h.cid===r,y=t===u,b=h.cid===i,S=Boolean(!o&&v)
return E.default.createElement("li",{"data-cid":t,className:"rn-content-item"},E.default.createElement(k.default,{depth:a,screen:h,isLinked:y,isActive:g,isEditing:b,hoverCid:d,showExpander:S,renderItem:f,collapseKeySet:c,handleScreenItemActions:p}),v&&m&&E.default.createElement("ol",{type:"screen-list",className:"child-screens"},v.map(function(e){var t=e.cid
return E.default.createElement(w,{key:t,cid:t,targetlinkCid:u,depth:a+1,collapseKeySet:c,isSearching:o,editingCid:i,hoverCid:d,activeCid:r,screenDataMap:s,screenTreeMap:l,treeProps:n})})))}}]),w}(E.PureComponent);(0,u.default)(h,"propTypes",{cid:d.default.string,treeProps:d.default.object,depth:d.default.number,isSearching:d.default.bool,editingCid:d.default.string,hoverCid:d.default.string,targetlinkCid:d.default.string,activeCid:d.default.string,screenTreeMap:d.default.object,
screenDataMap:d.default.object,collapseKeySet:d.default.object})},"m/Xg":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=n("xQM3"),m=n("CpT9"),v=r(n("p6mf")),g=function(e){function t(e){var u
return(0,i.default)(this,t),u=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(u),"handleMouseDown",function(e){if(!MB.isMobile()&&!u.props.isImmersive){var t=$(e.target).closest(".map_view .image"),n=$(e.target).closest(".ppanel"),a=t[0]||n[0]
if(a&&(a.clientWidth!==a.scrollWidth||a.clientHeight!==a.scrollHeight)){var r=e.clientX,i=e.clientY,o=a.scrollTop,l=a.scrollLeft,s=0,c=function(e){e.preventDefault(),s++,a.scrollTop=o-(e.clientY-i),a.scrollLeft=l-(e.clientX-r)}
document.addEventListener("mousemove",c),document.addEventListener("mouseup",function e(t){5<s&&MB.runner.eventBucket.isCoolDown(),document.removeEventListener("mousemove",c),document.removeEventListener("mouseup",e)})}}}),u.state={homeScreen:Screen.find(e.screen.cid)},u}return(0,u.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.project,n=e.screen,a=e.isLite,r=e.isScreenExpanded,i=e.viewportWidth,o=e.viewportHeight,l=t.splash,s=void 0===l?"":l,c=this.state.homeScreen,u={
width:i,height:o},d=(0,h.getScreenContainerStyle)(n,t,u,a,r),f=(0,m.getScreenClassName)(n,t)
return p.default.createElement("div",{id:"simulator",className:f,style:d,onMouseDown:this.handleMouseDown},p.default.createElement("div",{id:"app"},p.default.createElement(v.default,null)),p.default.createElement(y,{homeScreen:c,url:s}))}}]),t}(p.PureComponent)
t.default=g,(0,d.default)(g,"propTypes",{screen:f.default.object.isRequired,project:f.default.object.isRequired,isLite:f.default.bool,isImmersive:f.default.bool,isScreenExpanded:f.default.bool,viewportWidth:f.default.number,viewportHeight:f.default.number})
var y=function(e){function t(){return(0,i.default)(this,t),(0,l.default)(this,(0,s.default)(t).apply(this,arguments))}return(0,u.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e,t=this.props,n=t.homeScreen,a=t.url
return e=n.w()>n.dH()?{top:0-n.dW(),width:n.dH(),height:n.dW()}:{top:0,width:n.dW(),height:"101%"},p.default.createElement("div",{className:"splash",style:{backgroundColor:n.bg()}},a&&p.default.createElement("img",{src:a,style:e}),p.default.createElement("div",{className:"loading"},p.default.createElement("div",{className:"spinner"})))}}]),t}(p.PureComponent);(0,d.default)(y,"propTypes",{homeScreen:f.default.object,url:f.default.string})},m48X:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("pVnL")),o=r(n("QILm")),l=r(n("lwsE")),s=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("7W2i")),f=r(n("lSNA")),p=a(n("q1tI")),h=r(n("17x9")),m=n("6XO9")
n("WcC0")
var v=function(e){function t(){return(0,l.default)(this,t),(0,c.default)(this,(0,u.default)(t).apply(this,arguments))}return(0,d.default)(t,e),(0,s.default)(t,[{key:"render",value:function(){var e=this.props,t=e.className,n=e.menuClassName,a=(0,o.default)(e,["className","menuClassName"])
return p.default.createElement(m.Select,(0,i.default)({className:(0,m.trimList)(["ToolbarSelect",t]),menuClassName:(0,m.trimList)(["ToolbarSelectMenu",n])},a,{placeholder:" ",unstyled:!0,size:"small",menuX:"center"}))}}]),t}(p.PureComponent)
t.default=v,(0,f.default)(v,"propTypes",{className:h.default.string,menuClassName:h.default.string})},"mC/1":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledResetButton=t.StyledMainContent=void 0
var r=a(n("vOnD")),i=r.default.div.withConfig({displayName:"styles__StyledMainContent",componentId:"t5mjug-0"})(["flex:1;position:relative;width:100%;height:100%;pointer-events:none;"])
t.StyledMainContent=i
var o=r.default.div.withConfig({displayName:"styles__StyledResetButton",componentId:"t5mjug-1"})([
"position:absolute;top:38px;right:0;min-width:92px;padding:0 8px;height:28px;margin-right:27px;font-size:12px;white-space:nowrap;background:white;border-radius:2px;cursor:pointer;box-shadow:0 2px 5px 0 rgba(39,54,78,0.08);display:flex;justify-content:center;align-items:center;opacity:0;pointer-events:none;transition:opacity 0.2s ease-in-out;&:hover{background:#f5f5f5;color:#5b6b73;}&.is-show{pointer-events:auto;opacity:1;}"])
t.StyledResetButton=o},mCdf:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var c=a(n("MVZn")),i=a(n("lwsE")),o=a(n("W8MJ")),l=a(n("a1gu")),s=a(n("Nsbk")),u=a(n("PJYZ")),d=a(n("7W2i")),p=a(n("lSNA")),f=a(n("q1tI")),r=a(n("17x9")),h=n("ZXhj"),m=n("1qiG"),v=function(e){function r(){var e,f;(0,i.default)(this,r)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return f=(0,l.default)(this,(e=(0,s.default)(r)).call.apply(e,[this].concat(n))),(0,p.default)((0,u.default)(f),"getAuxiliaryLinesStyle",function(e,t){return{top:(0,m.toPercentage)(e.top/t.height),left:(0,m.toPercentage)(e.left/t.width),width:(0,m.toPercentage)(e.width/t.width),height:(0,m.toPercentage)(e.height/t.height)}}),(0,p.default)((0,u.default)(f),"getAuxiliaryLinesLength",function(){var e={},t=f.props,n=t.baseRect,a=t.refRect,r=(0,h.getMinContainingRect)(n,a),i=r.width-a.width
0<r.height-(n.height+a.height)&&i>n.width/2&&(e.horizontal=i)
var o=r.height-a.height
return 0<r.width-(n.width+a.width)&&o>n.height/2&&(e.vertical=o),e}),(0,p.default)((0,u.default)(f),"getLineStyle",function(e,t){var n=f.props,a=n.baseRect,r=n.refRect,i=a.left>r.left,o=a.top>r.top,l={}
if(e){var s,c=e/r.width
l.horizontal=(s={},(0,p.default)(s,o?"bottom":"top",0),(0,p.default)(s,i?"right":"left",(0,m.toPercentage)(-c)),(0,p.default)(s,"width",(0,m.toPercentage)(c)),s)}if(t){var u,d=t/r.height
l.vertical=(u={},(0,p.default)(u,i?"right":"left",0),(0,p.default)(u,o?"bottom":"top",(0,m.toPercentage)(-d)),(0,p.default)(u,"height",(0,m.toPercentage)(d)),u)}return l}),f}return(0,d.default)(r,e),(0,o.default)(r,[{key:"render",value:function(){var e=this.props,t=e.refRect,n=e.screen,a=e.style,r=this.getAuxiliaryLinesLength(),i=r.horizontal,o=r.vertical
if(!i&&!o)return null
var l=this.getAuxiliaryLinesStyle(t,n),s=this.getLineStyle(i,o)
return f.default.createElement("div",{className:"smart-auxiliary-lines",style:l},i&&f.default.createElement("div",{className:"line horizontal",style:(0,c.default)({},s.horizontal,{borderTopStyle:"".concat(a.dashed?"dashed":"solid"),borderTopColor:a.colorForLines})}),o&&f.default.createElement("div",{className:"line vertical",style:(0,c.default)({},s.vertical,{borderLeftStyle:"".concat(a.dashed?"dashed":"solid"),borderLeftColor:a.colorForLines})}))}}]),r}(f.default.Component);(t.default=v).propTypes={
baseRect:r.default.object,refRect:r.default.object,screen:r.default.object,style:r.default.object}},mMVB:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),p=a(n("q1tI")),h=n("/MKj"),m=r(n("bNtH")),v=function(e){function i(){var e,t;(0,o.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(a))),(0,f.default)((0,u.default)(t),"handleScroll",function(e){return t.props.dispatch({type:"entry:preview:set:canvas:offset",payload:{offset:e}})}),t}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props,t=e.canvasOffset,n=e.screen,a=e.scale,r=e.viewport,i=r.width,o=r.height,l={x:Math.max(3.5*i,n.width*a/100*2),y:Math.max(3.5*o,n.height*a/100*2)}
return p.default.createElement(m.default,{canvasOffset:t,viewportWidth:i,viewportHeight:o,canvasRange:l,onScroll:this.handleScroll})}}]),i}(p.PureComponent);(0,f.default)(v,"propTypes",{canvasOffset:i.default.object,dispatch:i.default.func,scale:i.default.number,screen:i.default.object,viewport:i.default.object})
var g=(0,h.connect)(function(e){var t=e.container.common,n=t.offset,a=t.scale,r=t.viewport,i=e.model,o=i.current.screenCid
return{canvasOffset:n,scale:a,screen:i.screens.find(function(e){return e.cid===o}),viewport:r}})(v)
t.default=g},mesP:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=a(n("BVfv")),o=(0,r.connect)(function(e){var t=e.model.user,n=e.container.previewSetting
return{isLogin:Boolean(t.id),unit:n.unit,emPixel:n.emPixel,ratio:n.ratio,language:n.language,isShowColorPicker:n.isShowColorPicker,colorUnit:n.colorUnit}})(i.default)
t.default=o},mggN:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.listItem=t.disabled=t.textEllipsis=void 0
var a=n("vOnD"),r=(0,a.css)(["white-space:nowrap;overflow:hidden;text-overflow:ellipsis;"])
t.textEllipsis=r
var i=(0,a.css)(["position:relative;pointer-events:none;&::after{content:'';position:absolute;top:0;left:0;width:100%;height:100%;cursor:not-allowed;pointer-events:auto;}"])
t.disabled=i
var o=(0,a.css)(["position:relative;height:32px;padding-left:14px;display:flex;align-items:center;border:1px solid transparent;color:",";cursor:pointer;.expander{width:12px;margin-top:1px;margin-left:-12px;text-align:center;color:",
";}.editable-span{margin-right:14px;width:100%;height:24px;line-height:22px;overflow:hidden;}.actions{display:none;position:absolute;top:0;right:0;height:100%;padding-left:6px;background:inherit;.Dropdown > button{display:flex;padding:8px 10px;padding-left:0;}.action{margin-right:6px;font-size:12px;color:",";&:hover{color:",";}}&.is-active{display:flex;align-items:center;color:#298df8;}}&:hover{.actions{display:flex;align-items:center;color:#8d9ea7;}}&:hover,&.hover{color:",";background:",
";}&.active{color:",";background:",";}"],function(e){return e.theme.listItem.tc},function(e){return e.theme.listItem.expander_color},function(e){return e.theme.listItem.action_color},function(e){return e.theme.listItem.action_hover_color},function(e){return e.theme.listItem.hover.tc},function(e){return e.theme.listItem.hover.bg},function(e){return e.theme.listItem.active.tc},function(e){return e.theme.listItem.active.bg})
t.listItem=o},mreW:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.entryMap=void 0
var r=a(n("MVZn")),o=a(n("zkrS")),i=n("2eJi"),l=n("upRB"),s=(0,r.default)({},i.entryMap,{"entry:state:init":function(e){var t=e.dispatch
t({type:"user:set",payload:o.default.MB.user||void 0}),t({type:"teams:refresh"}),t({type:"widgets:refresh"}),t({type:"projects:refresh"}),t({type:"screens:refresh"}),t({type:"collaborators:refresh"}),t({type:"entry:add-mock-collaborator"}),t({type:"entry:current:set",payload:{project:o.default.MB.currentProject,screen:o.default.MB.currentScreen}})},"entry:state:clear":function(e){e.dispatch},"entry:sync-runner:set-screen":function(e,t){var n=e.dispatch,a=e.getState,r=t.payload.cid
n({type:"entry:current:set-screen",payload:{cid:r}})
var i=a()
r!==(0,l.getRunnerState)(i).activeCid&&("inspect"===(0,l.getCurrentMode)(i)&&n({type:"SET_VISIBILITY_SCREEN",payload:{screenID:r}}),o.default.MB.runner.timerHandler.clear(),n({type:"entry:runner:activate:screen",payload:{screenCid:r,transition:void 0}}))},"entry:refresh:team-related":function(e){var t=e.dispatch
t({type:"teams:refresh"}),t({type:"collaborators:refresh"}),t({type:"entry:add-mock-collaborator"}),t({type:"entry:current:set",payload:{project:o.default.MB.currentProject,screen:o.default.MB.currentScreen}})},"entry:refresh:project-related":function(e){var t=e.dispatch
t({type:"projects:refresh"}),t({type:"screens:refresh"}),t({type:"widgets:refresh"}),t({type:"collaborators:refresh"}),t({type:"entry:add-mock-collaborator"}),t({type:"entry:current:set",payload:{project:o.default.MB.currentProject,screen:o.default.MB.currentScreen}})},"entry:preview:clear":function(e,t){var n=e.dispatch
n({type:"reducer:preview-panel:reset"}),n({type:"container:layers:clear"})}})
t.entryMap=s},mxnB:function(e,t,n){},nQhf:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("MVZn")),o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("7W2i")),d=a(n("q1tI")),f=r(n("17x9")),p=n("/MKj"),h=r(n("8jgF")),m=function(e){function t(){return(0,o.default)(this,t),(0,s.default)(this,(0,c.default)(t).apply(this,arguments))}return(0,u.default)(t,e),(0,l.default)(t,[{key:"render",value:function(){var e=this.props,t=e.open,n=e.event,a=e.loggedIn,r=e.inMobile,i=e.dispatch
return d.default.createElement("div",null,t&&!a&&d.default.createElement(h.default,{inMobile:r,event:n,isOpen:t,onClose:function(){return i("event-sign-up:close:modal")}}))}}]),t}(d.PureComponent)
m.propTypes={open:f.default.bool,inMobile:f.default.bool,event:f.default.object,loggedIn:f.default.bool,dispatch:f.default.func}
var v=(0,p.connect)(function(e){return(0,i.default)({},e.container.eventSignUpModal,{loggedIn:!!e.model.user.id,inMobile:MB.isMobile()})})(m)
t.default=v},nU12:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.reducerMap=t.entryMap=void 0
var u=a(n("lSNA")),r=a(n("MVZn")),i=n("WVP6"),c=a(n("iScx")),d=a(n("TZdj")),f=a(n("uW4e")),p=a(n("4YeV")),h=a(n("Emwt")),l=a(n("ni9f")),o=a(n("flWF")),m=a(n("HFhh")),v=a(n("JXIg")),g=a(n("zkrS")),y=n("oose"),b=n("tQ2B"),s=(0,r.default)({},c.default.entryMap,d.default.entryMap,f.default.entryMap,p.default.entryMap,h.default.entryMap,l.default.entryMap,o.default.entryMap,m.default.entryMap,v.default.entryMap,{"entry:add-mock-collaborator":function(e){var a=e.dispatch,t=l.default.getState(),
n=p.default.getState(),r=c.default.getState(),i=new Set(r.map(function(e){return e.cid})),o=function(e,t){var n="co_MOCK_".concat(e.cid)
i.has(n)||(a({type:"collaborators:add-local",payload:{cid:n,role:"owner",user_id:e.owner_id,name:e.owner_name,email:e.owner_email||"email_MOCK_".concat(e.owner_id),avatar:e.owner_avatar,team_cid:t?e.cid:null,project_cid:t?null:e.cid}}),0)}
t.forEach(function(e){return o(e,!0)}),n.forEach(function(e){return o(e,!1)})},"entry:current:set":function(e,t){var n=e.dispatch,a=t.payload,r=a.project,i=a.screen,o=v.default.getState(),l=r&&r.cid||o.projectCid,s=i&&i.cid||o.screenCid
n({type:"current:set",payload:{project:r=p.default.getState().find(function(e){return e.cid===l}),screen:i=h.default.getState().find(function(e){return e.cid===s}),userCollaborator:r&&function(t,n){var a=m.default.getState()
return a&&c.default.getState().find(function(e){return e.user_id===a.id&&(e.project_cid===t||e.team_cid===n)})}(r.cid,r.team_cid)}})},"entry:current:set-screen":function(e,t){var n=e.dispatch,a=t.payload.cid,r=h.default.getState().find(function(e){return e.cid===a})
if(!r)return console.warn("[entry:current:set-screen] non exist screen with cid: ".concat(a))
n({type:"entry:current:set",payload:{screen:r}})},"entry:comment:init-project-data":function(e){var l=e.dispatch,s=v.default.getState().projectCid,c=p.default.getState().find(function(e){return e.cid===s});(0,y.fetchProjectComment)({projectCid:s,projectAccessToken:c.access_token}).then(function(e){var t=e.org,n=e.team,a=e.members,r=e.threads,i=e.comments;(0,b.refreshCommentData)({comments:i,threads:r}),l({type:"comment-threads:refresh"}),l({type:"comments:refresh"}),l({type:"screens:refresh"})
var o={isProjectAllowComment:"allow"===(0,y.getProjectAllowCommentStatus)(c),projectAccessMap:(0,u.default)({},c.owner_id,"project_owner"),teamAccessMap:t&&t.accesses||{},orgAccessMap:n&&n.accesses||{},memberList:a||[]}
l({type:"container:comment:loaded-project",payload:{projectCid:s,projectCommentData:o}})})},"entry:comment-threads:add":function(e,t){e.getState
var n=e.dispatch,a=t.payload,r=a.top,i=a.left,o=a.message,l=m.default.getState(),s=v.default.getState().screenCid,c=.001*Date.now(),u=g.default.SpineModel.requestCid("cmth")
n({type:o?"comment-threads:add":"comment-threads:add-local",payload:{cid:u,top:r,left:i,screen_cid:s,user_id:l.id,created_at:c,updated_at:c}}),o&&n({type:"comments:add",payload:{thread_cid:u,message:o,user_id:l.id,created_at:c,updated_at:c}}),n({type:"container:comment:focus",payload:{focusCommentThreadCid:u}})},"entry:comment-threads:update":function(e,t){var n=e.dispatch,a=(e.getState,t.payload),r=a.cid,i=a.top,o=a.left,l=void 0===d.default.getState().find(function(e){return e.thread_cid===r}),
s=.001*Date.now()
n({type:l?"comment-threads:update-local":"comment-threads:update",payload:{cid:r,top:i,left:o,updated_at:s}})},"entry:comment-threads:delete":function(e,t){var n=e.dispatch,a=t.payload.cid
n({type:"comment-threads:delete",payload:{cid:a}}),d.default.getState().forEach(function(e){return e.thread_cid===a&&n({type:"comments:delete-local",payload:e})})},"entry:comments:add":function(e,t){var n=e.dispatch,a=t.payload,r=a.thread_cid,i=a.message,o=m.default.getState(),l=.001*Date.now()
n({type:"comment-threads:save",payload:{cid:r}}),n({type:"comments:add",payload:{thread_cid:r,message:i,user_id:o.id,created_at:l,updated_at:l}}),n({type:"container:comment:focus",payload:{focusCommentThreadCid:null}})},"entry:comments:update":function(e,t){var n=e.dispatch,a=t.payload
n({type:"comments:update",payload:{cid:a.cid,message:a.message,updated_at:.001*Date.now()}})},"entry:state:push-data":function(e,t){var n=e.dispatch,a=t.payload,r=a.pushType,i=a.action,o=a.data
switch(r){case"comment-threads":var l=f.default.getState().find(function(e){return e.cid===o.cid})
"update"!==i||l?"update"===i&&l?n({type:"comment-threads:update-local",payload:o}):"destroy"===i&&l&&(n({type:"comment-threads:delete-local",payload:o}),d.default.getState().forEach(function(e){return e.thread_cid===o.cid&&n({type:"comments:delete-local",payload:e})})):n({type:"comment-threads:add-local",payload:o})
break
case"comments":var s=d.default.getState().find(function(e){return e.cid===o.cid})
"update"!==i||s?"update"===i&&s?n({type:"comments:update-local",payload:o}):"destroy"===i&&s&&n({type:"comments:delete-local",payload:o}):n({type:"comments:add-local",payload:o})}}})
function S(n,e){var a=e.getState,r=e.setState,i=a()
return function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:i,t=1<arguments.length?arguments[1]:void 0
return t.type!==n?e:(r(t.payload||e),a())}}t.entryMap=s
var w={collaborators:S("reducer:collaborators:update",c.default),comments:S("reducer:comments:update",d.default),commentThreads:S("reducer:comment-threads:update",f.default),projects:S("reducer:projects:update",p.default),screens:S("reducer:screens:update",h.default),teams:S("reducer:teams:update",l.default),widgets:S("reducer:widgets:update",o.default),user:(0,i.createStateStoreReducer)("reducer:user:update",m.default),current:(0,i.createStateStoreReducer)("reducer:current:update",v.default)}
t.reducerMap=w},naIL:function(e,t,n){e.exports={"screen-panel":"xcKB8zcEhkyUcti-3naYu"}},ni9f:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("WVP6"),r=n("Ehhz").MODEL_OPERATION_MAP.Team,i=(0,a.createStateStore)([]),o=i.getState,l=i.setState,s=i.wrapEntry,c=function(i,o){return s(function(e,t,n){var a=t.dispatch,r=n&&n.payload
a({type:"reducer:teams:update",payload:i(e,r,o)})})},u={entryMap:{"teams:refresh":c(r.refreshStateList,!1),"teams:add":c(r.addState,!1),"teams:add-local":c(r.addState,!0),"teams:update":c(r.updateState,!1),"teams:update-local":c(r.updateState,!0),"teams:delete":c(r.deleteState,!1),"teams:delete-local":c(r.deleteState,!0)},getState:o,setState:l}
t.default=u},"o/90":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),l=r(n("7W2i")),d=r(n("lSNA")),f=r(n("RIqP")),p=r(n("17x9")),h=a(n("q1tI")),m=r(n("DKAG")),v=r(n("p2ZH")),g=r(n("2b0G")),y=r(n("4QcC")),b=r(n("ER7e")),S=r(n("Kurm")),w=r(n("TSYQ")),E=function(e){var t=document.querySelector(".full-screen header"),n=document.querySelector(".full-screen #mb-preview-leftpane"),a=document.querySelector(".full-screen #mb-preview-rightpane"),r=document.querySelector("#preview_scrollBar_viewport"),
i=Array.from(r.querySelectorAll(".track, .handler")),o=document.querySelector("#simulator-container"),l=[t,n,a].concat((0,f.default)(i)).filter(function(e){return e})
"hide"===e?(o.style.overflow="visible",l.forEach(function(e){return e.style.opacity=0}),setTimeout(function(){return l.forEach(function(e){return e.style.pointerEvents="none"})},300)):"show"===e&&(o.style.overflow="hidden ",l.forEach(function(e){return e.style.pointerEvents="auto"}),setTimeout(function(){return l.forEach(function(e){return e.style.opacity=1})},300))},k=function(e){function t(e){var l
return(0,i.default)(this,t),l=(0,s.default)(this,(0,c.default)(t).call(this,e)),(0,d.default)((0,u.default)(l),"setMode",function(e){var t=l.state.isDarkMode,n=e.target.dataset.mode
"light"===n&&t&&l.setState({isDarkMode:!1}),"dark"!==n||t||(MB.event("preview","工具栏: 全屏模式暗色背景"),l.setState({isDarkMode:!0}))}),(0,d.default)((0,u.default)(l),"handleKeyDown",function(e){37===e.keyCode&&l.goToScreenByStep(-1),39===e.keyCode&&l.goToScreenByStep(1)}),(0,d.default)((0,u.default)(l),"handleNavigate",function(e){var t=e.currentTarget.dataset.action
"last"===t?(MB.event("*","运行页-预览-全屏模式-点击上一页"),l.goToScreenByStep(-1)):"next"===t&&(MB.event("*","运行页-预览-全屏模式-点击下一页"),l.goToScreenByStep(1))}),(0,d.default)((0,u.default)(l),"handleExitFullScreen",function(){l.props.dispatch({type:"entry:exit:fill-screen-mode"})}),(0,d.default)((0,u.default)(l),"goToScreenByStep",function(e){var t=l.props,n=t.screen,a=t.screenInOrder,r=t.dispatch,i=n.cid,o=a.findIndex(function(e){return e===i})+e
if(o<0)l.setState({shouldTextShow:!0,reachFirstScreen:!0})
else if(o>a.length-1)l.setState({shouldTextShow:!0,reachLastScreen:!0})
else{r({type:"entry:sync-runner:set-screen",payload:{cid:a[o]}}),r({type:"preview:set:canvas:offset",payload:{offset:{x:0,y:0}}}),l.setState({shouldTextShow:!0,reachFirstScreen:!1,reachLastScreen:!1})}}),l.state={isDarkMode:!1,shouldTextShow:!1,reachFirstScreen:!1,reachLastScreen:!1},l}return(0,l.default)(t,e),(0,o.default)(t,[{key:"componentDidMount",value:function(){E("hide")}},{key:"componentWillUnmount",value:function(){E("show")}},{key:"componentDidUpdate",value:function(e){var t=this
if(this.state.shouldTextShow&&(clearTimeout(this.timer),this.timer=setTimeout(function(){return t.setState({shouldTextShow:!1})},1500)),this.props.screen!==e.screen){var n=this.props,a=n.screen,r=n.screenInOrder,i=a.cid,o=r.findIndex(function(e){return e===i})
0!==o&&this.setState({reachFirstScreen:!1}),o!==r.length-1&&this.setState({reachLastScreen:!1})}}},{key:"render",value:function(){var e=this.state,t=e.isDarkMode,n=e.shouldTextShow,a=e.reachFirstScreen,r=e.reachLastScreen,i=this.props,o=i.screen,l=i.screenInOrder,s=i.dispatch,c=i.scale
return h.default.createElement("div",{className:(0,w.default)(S.default["full-screen-actions"],{"dark-mode":t})},h.default.createElement("div",{className:(0,w.default)("zoom-wrapper",{"is-Iniframe":MB.isUIChina()||MB.isForum()})},h.default.createElement(y.default,{fromFullScreen:!0,scale:c,dispatch:s})),h.default.createElement(b.default,{onClickMode:this.setMode,onClickExit:this.handleExitFullScreen}),h.default.createElement(v.default,{screen:o,screenInOrder:l,shouldTextShow:n,reachFirstScreen:a,
reachLastScreen:r}),h.default.createElement(g.default,{onClick:this.handleNavigate}),h.default.createElement(m.default,{target:document,onKeyDown:this.handleKeyDown}))}}]),t}(h.PureComponent)
t.default=k,(0,d.default)(k,"propTypes",{dispatch:p.default.func,screen:p.default.object,screenInOrder:p.default.array,scale:p.default.number})},oKLx:function(e,t,n){},oQ6s:function(e,t,n){},oSKl:function(e,t,n){},oose:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),Object.defineProperty(t,"reducer",{enumerable:!0,get:function(){return c.reducer}}),Object.defineProperty(t,"fetchProjectComment",{enumerable:!0,get:function(){return u.fetchProjectComment}}),t.getProjectAllowCommentStatus=t.CommentContainer=t.CommentMarkerPanelContainer=void 0
var r=n("/MKj"),i=a(n("zkrS")),o=n("/5+U"),l=n("3xeE"),s=n("94Et"),m=n("rbsZ"),c=n("ZY2Q"),v=n("fiFu"),u=n("VQzC"),d=i.default.I18N,f=(0,r.connect)(function(e){var t=e.model,n=t.user.id,a=t.current,r=(a.userRole,a.screenCid),i=a.projectCid,o=(a.teamCid,t.projects),l=t.screens,s=(t.collaborators,t.commentThreads),c=t.comments,u=e.container.comment,d=u.loadedProjectCid,f=u.loadedProjectCommentData,p=u.focusCommentThreadCid,h=u.focusSource,m=u.tempCommentThreadMarker
return{isLoaded:d===i,permissionPack:S(o,i,n,f),getUserProfile:w(f),screenName:b(l,r),commentThreadList:g(s,r),commentListMap:y(c),focusCommentThreadCid:p,focusSource:h,tempCommentThreadMarker:m}})(l.CommentLayer)
t.CommentContainer=f
var p=(0,r.connect)(function(e){var t=e.model,n=t.user.id,a=t.current,r=(a.userRole,a.screenCid),i=a.projectCid,o=(a.teamCid,t.projects),l=(t.collaborators,t.commentThreads),s=e.container.comment,c=s.loadedProjectCid,u=s.loadedProjectCommentData,d=s.focusCommentThreadCid,f=(s.focusSource,s.tempCommentThreadMarker)
return{isLoaded:c===i,permissionPack:S(o,i,n,u),markerDomPack:E(r),commentThreadList:g(l,r),focusCommentThreadCid:d,tempCommentThreadMarker:f}})(s.CommentMarkerPanel)
t.CommentMarkerPanelContainer=p
var g=(0,o.immutableTransformCache)(function(e,t){return e.filter(function(e){return e.screen_cid===t})}),y=(0,o.immutableTransformCache)(function(e){return e.reduce(function(e,t){return void 0===e[t.thread_cid]?e[t.thread_cid]=[t]:e[t.thread_cid].push(t),e},{})}),b=(0,o.immutableTransformCache)(function(e,t){return e.find(function(e){return e.cid===t}).name}),S=(0,o.immutableTransformCache)(function(e,t,n,a){if(!a)return{isProjectAllowComment:!1,getPermission:function(){return!1},permissionDenyMessage:"",
userAuthStatus:(0,v.getUserAuthStatus)(n,[])}
var r=a.isProjectAllowComment,i=a.projectAccessMap,o=a.teamAccessMap,l=a.orgAccessMap,s=a.memberList,c=[i[n],o[n],l[n]].filter(Boolean).join("|")
console.log("userTitleString")
var u,d,f=Boolean(c),p=c.includes("admin")||c.includes("owner"),h=(0,v.getCommentPermission)()
return{isProjectAllowComment:r,getPermission:r?function(e){return(0,v.getCommentPermission)(f,p,n,e)}:function(){return h},permissionDenyMessage:r?"":(u=e.find(function(e){return e.cid===t}),d=k(u),(0,m.getRenewMessage)("comment_".concat(d),{action:"comment_".concat(d)})),userAuthStatus:(0,v.getUserAuthStatus)(n,s)}}),w=(0,o.immutableTransformCache)(function(e){var t=e&&e.memberList.reduce(function(e,t){var n=t.user_id,a=t.avatar,r=t.name
return e[n]={avatar:a,name:r},e},{})||{}
return function(e){return t[e]||h}}),h={name:d.preview.comment.user_name_ghost,avatar:"/images/avatar.png"},E=(0,o.immutableTransformCache)(function(e){return{getScreenContainerElement:function(){return document.querySelector("#pscreen".concat(e," .scontainer"))},getSimulatorContainerElement:function(){return document.querySelector("#simulator-container")}}}),k=function(e){
return!e||e.combo||e.template?"deny":e.limitation.commentable?"org_member"!==e.comment_permission?"deny_permission":"allow":"deny_limitation"}
t.getProjectAllowCommentStatus=k},os03:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.withTimeoutRetry=t.createSaveQueue=void 0
var f=a(n("o0o1")),p=a(n("yXPU")),h=n("ZiVu"),m=function(){}
t.createSaveQueue=function(e){var t=e.onError,r=e.doSave,n=e.beforeSave,i=void 0===n?m:n,a=e.afterSave,o=void 0===a?m:a,l=[],s=!1,c={},u=function(e){c=e},d=function(){var e=(0,p.default)(f.default.mark(function e(){var t,n,a
return f.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return i(),t=l,l=[],s=!0,e.next=6,(0,h.catchAsync)(r,t,u)
case 6:if(n=e.sent,a=n.error,s=!1,c={},a&&console.error("[Error][saveAsync] savingDataQueue: ".concat(t.length,", dataQueue: ").concat(l.length),a),a)throw a
e.next=13
break
case 13:o()
case 14:case"end":return e.stop()}},e)}))
return function(){return e.apply(this,arguments)}}()
return{clear:function(){l=[]},add:function(e){return l.push(e)},save:function(){!s&&l.length&&d().catch(t)},filter:function(e){l=l.filter(e)},getLength:function(){return l.length},getIsSaving:function(){return s},getSavingState:function(){return c}}}
var r=function(){var t=(0,p.default)(f.default.mark(function e(t){var n,a,r,i,o,l
return f.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:n=t.task,a=t.onError,r=t.timeout,i=t.retry,o=void 0===i?8:i,l=0
case 2:return e.prev=3,e.next=6,Promise.race([n({attempt:l,timeout:r}),new Promise(function(e,t){return setTimeout(function(){return t(new Error("[TIMEOUT] timeout after ".concat(r)))},r)})])
case 6:return e.abrupt("return",e.sent)
case 9:if(e.prev=9,e.t0=e.catch(3),o<=l)throw e.t0
e.next=13
break
case 13:return e.next=15,a(e.t0,{attempt:l,timeout:r})
case 15:l++
case 16:e.next=2
break
case 18:case"end":return e.stop()}},e,null,[[3,9]])}))
return function(e){return t.apply(this,arguments)}}()
t.withTimeoutRetry=r},p2ZH:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("7W2i")),u=r(n("lSNA")),d=r(n("17x9")),f=a(n("q1tI")),p=r(n("6PGs")),h=r(n("TSYQ")),m=function(e){function t(){return(0,i.default)(this,t),(0,l.default)(this,(0,s.default)(t).apply(this,arguments))}return(0,c.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e,t=this.props,n=t.screen,a=t.screenInOrder,r=t.shouldTextShow,i=t.reachFirstScreen,o=t.reachLastScreen,l=a.findIndex(function(e){return e===n.cid})
return e=i?I18N.preview.firstScreen:o?I18N.preview.lastScreen:"".concat(l+1," / ").concat(a.length),f.default.createElement("div",{className:(0,h.default)(p.default["screen-info"],{show:r})},f.default.createElement("div",null,e),f.default.createElement("span",{className:"dot"}),f.default.createElement("div",{className:"screen-name"},n.name))}}]),t}(f.PureComponent)
t.default=m,(0,u.default)(m,"propTypes",{screen:d.default.object,screenInOrder:d.default.array,shouldTextShow:d.default.bool,reachFirstScreen:d.default.bool,reachLastScreen:d.default.bool})},p6mf:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=n("/MKj"),i=n("upRB"),o=a(n("6Y1W")),l=(0,r.connect)(function(e){return(0,i.getRunnerState)(e)})(o.default)
t.default=l},pVAx:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.RECOMMEND_LIBRARY_BASIC_WIDGETS=t.LIBRARY_BASIC_WIDGETS=t.LAYOUT_BG_COLOR=t.LAYOUT=t.LAYOUT_PADDING=t.BASIC_WIDGET_NAMES=t.RECOMMEND=t.CLASSIC=t.BETA=void 0
var a=n("abHt")
t.BETA="beta"
t.CLASSIC="classic"
t.RECOMMEND="recommend"
var r=["rich_text","rounded_rect","circle_rect","line","image_view","lr"]
t.BASIC_WIDGET_NAMES=r
t.LAYOUT_PADDING={h:20,v:10}
t.LAYOUT={row:{count:0,gutter:20,size:144},col:{count:4,gutter:20,size:0}}
t.LAYOUT_BG_COLOR="rgba(41, 141, 248, 0.24)"
var i=a.visibleComponentList.filter(function(e){return!r.includes(e.name)})
t.LIBRARY_BASIC_WIDGETS=i
var o=r.map(function(e){return a.componentMap[e]}).concat(i)
t.RECOMMEND_LIBRARY_BASIC_WIDGETS=o},peLG:function(e,t,n){},prTy:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("pVnL")),l=r(n("QILm")),s=r(n("o0o1")),c=r(n("yXPU")),u=r(n("lwsE")),d=r(n("W8MJ")),f=r(n("a1gu")),p=r(n("Nsbk")),h=r(n("PJYZ")),m=r(n("7W2i")),v=r(n("lSNA")),g=a(n("q1tI")),i=r(n("17x9")),y=n("QQiC"),b=n("/5+U"),S=(0,y.createAsyncTaskQueue)().pushTask,w=function(t,n){return new Promise(function(e){t.src=n,t.onload=function(){return e(t)},t.onerror=function(){return e()}})},E=function(e){function i(){var e,t;(0,u.default)(this,i)
for(var n=arguments.length,a=new Array(n),r=0;r<n;r++)a[r]=arguments[r]
return t=(0,f.default)(this,(e=(0,p.default)(i)).call.apply(e,[this].concat(a))),(0,v.default)((0,h.default)(t),"getElementRef",function(e){return t.imageRef=e}),t}return(0,m.default)(i,e),(0,d.default)(i,[{key:"componentDidMount",value:function(){var i=this
S((0,c.default)(s.default.mark(function e(){var t,n,a,r
return s.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return t=i.props,n=t.src,a=t.adjustImage,e.next=3,w(i.imageRef,n)
case 3:r=e.sent,a&&r&&(0,b.adjustImageRect)({image:r,adjust:a})
case 5:case"end":return e.stop()}},e)}))).catch(function(e){return console.error(e)})}},{key:"render",value:function(){var e=this.props,t=(e.src,e.adjustImage,(0,l.default)(e,["src","adjustImage"]))
return g.default.createElement("img",(0,o.default)({alt:"",ref:this.getElementRef},t))}}]),i}(g.PureComponent);(t.default=E).propTypes={src:i.default.string,adjustImage:i.default.number}},q3nj:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),Object.defineProperty(t,"reducerMap",{enumerable:!0,get:function(){return l.default}}),Object.defineProperty(t,"PreviewContainer",{enumerable:!0,get:function(){return s.default}}),t.sagaMap=void 0
var r=a(n("j1JO")),i=a(n("yOnP")),o=n("tBsX"),l=a(n("cQH5")),s=a(n("aYzi")),c={layerSaga:o.saga,sliceSaga:r.default,artboardsSaga:i.default}
t.sagaMap=c},qYFl:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.isRemoteMtimeStale=t.updateWorkspaceMap=t.updateProject=t.updateTeam=t.updateCollaborator=t.updateAsset=void 0
var c=a(n("o0o1")),r=a(n("yXPU")),u=n("t3Un"),i=n("t77w"),d=n("tQ2B"),o=window,l=o.$,f=o.MB,s=o.Screen,p=o.Screenstate,h=o.Panel,m=o.Panelstate,v=o.Widget,g=o.Widgetstate,y=o.Link
t.updateAsset=function(e,t){if(!f.f.inSharing&&"create"===e){var n=new Asset
n.load(t),n.lsave(!1)}}
t.updateCollaborator=function(e,t){if(f.f.inSharing){if("update"===e){var n=Collaborator.find(t.cid)
n?n.refresh(t):((n=new Collaborator).load(t),n.lsave(!1)),f.webpackInterface.store.dispatch({type:"entry:state:init"})}if("destroy"===e){var a=Collaborator.find(t.cid)
if(!a)return
if(a.ldestroy(!1),a.user_id===f.user.id)return window.location.reload()}}else{if("update"===e){var r=Collaborator.find(t.cid)
r?r.refresh(t):((r=new Collaborator).load(t),r.lsave(!1)),f.webpackInterface.refreshAll()}if("destroy"===e){var i=Collaborator.find(t.cid)
if(!i)return
if(i.ldestroy(!1),i.user_id===f.user.id){var o=i.project_cid&&Project.find(i.project_cid),l=i.team_cid&&Team.find(i.team_cid)
o&&f.webpackInterface.deleteProjectByCid(o.cid),l&&f.webpackInterface.deleteTeamByCid(l.cid)}}}}
t.updateTeam=function(e,t){if(!f.f.inSharing){if("update"===e){var n=Team.find(t.cid)
n?n.refresh(t):((n=new Team).load(t),n.lsave(!1)),f.webpackInterface.refreshAll()}if("destroy"===e){var a=Team.find(t.cid)
a&&f.webpackInterface.deleteTeamByCid(a.cid)}}}
t.updateProject=function(e,t){if(!f.f.inSharing){if("update"===e){var n=Project.find(t.cid)
if(n){if(n.duplicating){var a=n.screens_count
n.refresh(t),n.screens_count=a}}else(n=new Project).load(t),n.screens_count||(n.screens_count=2),n.lsave(!1)
f.webpackInterface.refreshAll(),n.duplicating||l("#notification").removeClass("active"),f.f.isDuplicatingDemo&&!n.duplicating&&(f.f.isDuplicatingDemo=!1,f.webpackInterface.navigateTo("/workspace/apps/".concat(n.cid)))}if("destroy"===e){var r=Project.find(t.cid)
if(r)f.webpackInterface.deleteProjectByCid(r.cid)
else{var i=Template.find(t.cid)
i&&(i.ldestroy(!1),f.renderTemplateList())}}l(".timeago").timeago()}}
var b={Screen:function(e,t){if("update"===e){var n=s.find(t.cid)
n?(n.refresh(t),f.currentScreen.cid===n.cid&&f.updateCurrentScreen()):((n=new s).load(t),n.lsave(!1)),f.currentProject&&f.currentProject.cid===n.project_cid&&f.action("update:screens:all",{screens:f.currentProject.cscreens()})}else if("destroy"===e){var a=s.find(t.cid)
if(!a)return
a.ldestroy(!1),f.currentProject&&f.currentProject.cid===a.project_cid&&f.action("entry:remove:from:screen-history",{cids:[a.cid]})}},Screenstate:function(e,t){var n=s.find(f.currentScreen.cid)
if("update"===e){var a=p.find(t.cid)
a?a.refresh(t):((a=new p).load(t),a.lsave(!1)),n&&n.cid===a.screen_cid&&f.updateCurrentScreen()}else if("destroy"===e){var r=p.find(t.cid)
if(!r)return
r.ldestroy(!1),n&&n.cid===r.screen_cid&&(n.state_cid===r.cid&&(n.setState("default",!0),f.action("set:current:screen",{screen:n}),ScreenManager.updateWidgetList()),f.updateCurrentScreen())}},Panel:function(){var a=(0,r.default)(c.default.mark(function e(t,n,a){var r,i,o,l,s
return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:if(r=f.getCurrentScreen(),"update"!==t){e.next=30
break}if(i=h.find(n.cid)){e.next=25
break}if(e.prev=4,Template.find(n.template_cid)){e.next=12
break}return e.next=9,(0,u.requestJSON)("/templates/".concat(n.template_cid,".json"))
case 9:o=e.sent,(0,d.refreshTemplateData)(o),f.Pusher.enableSocketChannel(o.template.cid)
case 12:if((l=new h).load(n),l.lsave(!1),f.renderTemplateList(),r===l.screen_cid)return e.abrupt("return",ScreenManager.updateWidgetList())
e.next=18
break
case 18:e.next=23
break
case 20:e.prev=20,e.t0=e.catch(4),console.warn(e.t0)
case 23:e.next=28
break
case 25:if(i.refresh(n),r===i.screen_cid)return e.abrupt("return",ScreenManager.updateWidgetList())
e.next=28
break
case 28:e.next=41
break
case 30:if("destroy"!==t){e.next=41
break}if(s=h.find(n.cid)){e.next=34
break}return e.abrupt("return")
case 34:if(r===s.screen_cid)return s.ldestroy(!1),f.action("selection:unselect:items",{cids:[s.cid]}),e.abrupt("return",ScreenManager.updateWidgetList())
e.next=40
break
case 40:return e.abrupt("return",s.ldestroy(!1))
case 41:case"end":return e.stop()}},e,null,[[4,20]])}))
return function(e,t,n){return a.apply(this,arguments)}}(),Panelstate:function(e,t){var n=s.find(f.currentScreen.cid)
if("update"===e){var a=m.find(t.cid)
if(a?a.refresh(t):((a=new m).load(t),a.lsave(!1)),n&&n.state_cid===a.screenstate_cid){var r=h.find(a.panel_cid)
r.screenstate_cid===a.screenstate_cid&&(r.restore(a),r.lsave(!1),ScreenManager.updateWidgetList())}}},Widget:function(e,t){return function(e,t){var n=f.getCurrentScreen()
if("update"===e){var a=v.find(t.cid)
a?a.refresh(t):((a=new v).load(t),a.lsave(!1)),n===a.screen_cid&&ScreenManager.updateWidgetList()}else if("destroy"===e){var r=v.find(t.cid)
if(!r)return
r.ldestroy(!1),n===r.screen_cid&&(f.action("selection:unselect:items",{cids:[r.cid]}),ScreenManager.updateWidgetList())}}(e,(0,i.decompressRichText)(t))},Widgetstate:function(e,t){return function(e,t){var n=s.find(f.currentScreen.cid)
if("update"===e){var a=g.find(t.cid)
if(a?a.refresh(t):((a=new g).load(t),a.lsave(!1)),n&&n.state_cid===a.screenstate_cid){var r=v.find(a.widget_cid)
r.screenstate_cid===a.screenstate_cid&&(r.restore(a),r.lsave(!1),ScreenManager.updateWidgetList())}}}(e,(0,i.decompressRichText)(t))},Link:function(e,t){var n,a=f.getCurrentScreen()
if("update"===e)(n=y.find(t.cid))?n.refresh(t):((n=new y).load(t),n.lsave(!1))
else if("destroy"===e){if(!(n=y.find(t.cid)))return
n.ldestroy(!1)}n&&a===n.screen_cid&&f.renderLinks()}}
t.updateWorkspaceMap=b
var S={Asset:Asset,Collaborator:Collaborator,Team:Team,Project:Project,Screen:s,Screenstate:p,Panel:h,Panelstate:m,Widget:v,Widgetstate:g,Link:y}
t.isRemoteMtimeStale=function(e,t,n){var a=S[e]&&S[e].findByAttribute("cid",t)
return a&&a.mtime>n}},qc8Y:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledPreviewPanel=void 0
var r=a(n("vOnD")).default.div.withConfig({displayName:"styles__StyledPreviewPanel",componentId:"snkhg3-0"})([
"position:relative;width:240px;height:100%;font-size:12px;color:#525e71;background-color:#fff;box-shadow:0 -2px 30px rgba(39,54,78,0.11);header{height:32px;padding-left:10px;padding-right:12px;display:flex;justify-content:flex-end;background:#f2f3f4;overflow:hidden;.preview-panel-nav{height:26px;align-self:flex-end;background:transparent;& > li{width:60px;border-radius:4px 4px 0 0;transition:all 0.2s ease-out;.nav-icon{color:#5b6b73;.icon{font-size:14px;width:14px;height:14px;}.screen-icon{position:relative;margin-left:-17px;&::after{content:"
,";position:absolute;bottom:-5px;left:6px;font-size:20px;padding:0 5px 0 7px;min-width:36px;height:24px;border-radius:12px;background-color:#ededed;color:#415058;text-align:center;line-height:24px;transform:scale(0.5);}}}&.active .nav-icon{color:#ff6161;}:not(.active):hover{background:#fcfcfc;.nav-icon{.svg-icon{color:#5b6b73;.fore{fill:#8d9ea7;}}}}}.background-cube{background:#fff;box-shadow:0 -2px 7px 0 rgba(0,0,0,0.06);border-radius:4px 4px 0 0;}}}&.is-uichina{box-shadow:none;}"],function(e){
return"'".concat(e.screensCount,"'")})
t.StyledPreviewPanel=r},r2i6:function(e,t,n){t.__esModule=!0
var g=n("hGv0"),y=n("ax+U")
function r(){return(r=Object.assign||function(e){for(var t=1;t<arguments.length;t++){var n=arguments[t]
for(var a in n)Object.prototype.hasOwnProperty.call(n,a)&&(e[a]=n[a])}return e}).apply(this,arguments)}var b=function(e,t,n,a){return r({},(0,y.createNode)(t),{key:e,size:n,expireAt:a})}
t.createCache=b,t.createCacheMap=function(e){var i=e.valueSizeSumMax,t=e.valueSizeSingleMax,o=void 0===t?Math.max(.05*i,1):t,n=e.eventHub,a=void 0===n?(0,g.createHub)():n,r=Boolean(a),l=r?a:{},s=l.clear,c=l.subscribe,u=l.unsubscribe,d=l.send,f=new Map,p=(0,y.createDoublyLinkedList)(),h=0,m=function(e){f.set(e.key,e),p.unshift(e),h+=e.size,r&&d({type:"add",key:e.key,payload:e.value})},v=function(e){f.delete(e.key),p.remove(e),h-=e.size,r&&d({type:"delete",key:e.key,payload:e.value})}
return{hasEventHub:r,clearHub:s,subscribe:c,unsubscribe:u,clear:function(){return f.forEach(v)},getSize:function(){return f.size},getValueSize:function(){return h},set:function(e,t,n,a){void 0===n&&(n=1),void 0===a&&(a=Date.now()+6e4)
var r=f.get(e)
if(r&&v(r),!(o<n)){for(;i<n+h;)v(p.getTail().prev)
m(b(e,t,n,a))}},get:function(e,t){void 0===t&&(t=Date.now())
var n=f.get(e)
if(n)return n.expireAt<=t?v(n):(p.setFirst(n),n.value)},touch:function(e,t){void 0===t&&(t=Date.now()+6e4)
var n=f.get(e)
if(n)return n.expireAt=t,p.setFirst(n),n.value},delete:function(e){var t=f.get(e)
return t&&v(t),t&&t.value},packList:function(){var i=[]
return p.forEachReverse(function(e){var t=e.key,n=e.value,a=e.size,r=e.expireAt
return i.push({key:t,value:n,size:a,expireAt:r})}),i},parseList:function(e,o){return void 0===o&&(o=Date.now()),e.forEach(function(e){var t=e.key,n=e.value,a=e.size,r=e.expireAt,i=b(t,n,a,r)
i.expireAt<=o?v(i):m(i)})}}}},rESR:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var l=r(n("pVnL")),s=r(n("QILm")),i=r(n("lwsE")),o=r(n("W8MJ")),c=r(n("a1gu")),u=r(n("Nsbk")),d=r(n("PJYZ")),f=r(n("7W2i")),p=r(n("lSNA")),h=a(n("q1tI")),m=r(n("17x9")),v=a(n("DqDi")),g=a(n("i6OX")),y=r(n("xo+i")),b=n("gSgL"),S=n("qc8Y"),w=r(n("TSYQ")),E=[{key:"screen",icon:h.default.createElement(g.default,{type:"dora",className:"screen-icon",name:"file_text"}),title:I18N.preview.pages},{key:"images",icon:h.default.createElement(g.SVGIcon,{name:"design/slice_image"}),title:I18N.preview.images}],k=function(
e){function n(e){var t
return(0,i.default)(this,n),t=(0,c.default)(this,(0,u.default)(n).call(this,e)),(0,p.default)((0,d.default)(t),"setElementRef",function(e){return t.$elem=e}),(0,p.default)((0,d.default)(t),"handTooltip",function(){$(t.$elem).tooltip({selector:".preview-panel-nav li",container:"body",placement:"bottom",trigger:"hover"})}),(0,p.default)((0,d.default)(t),"handleTabChange",function(e){t.setState({activeIndex:e})}),t.state={activeIndex:0},t}return(0,f.default)(n,e),(0,o.default)(n,[{
key:"UNSAFE_componentWillReceiveProps",value:function(e){"inspect"!==e.toolbarActiveItem&&this.setState({activeIndex:0})}},{key:"componentDidMount",value:function(){this.handTooltip()}},{key:"render",value:function(){var e=this.props,t=e.isDemo,n=e.project,a=e.screensCount,r=e.toolbarActiveItem,i=this.state.activeIndex,o="inspect"==r&&!MB.isHTMLZip()?E:E.slice(0,1)
return h.default.createElement(S.StyledPreviewPanel,{className:(0,w.default)("preview-panel",{"is-uichina":MB.isUIChina()||MB.isForum()}),ref:this.setElementRef,screensCount:a},h.default.createElement("header",null,h.default.createElement(v.default,{className:"preview-panel-nav",activeIndex:i,onTabChange:this.handleTabChange},o.map(function(e){var t=e.key,n=(0,s.default)(e,["key"])
return h.default.createElement(v.NavItem,(0,l.default)({key:t},n))}))),0==i?h.default.createElement(y.default,{toolbarActiveItem:r,isDemo:t}):h.default.createElement(b.SliceContainer,{projectName:n.name}))}}]),n}(h.PureComponent)
t.default=k,(0,p.default)(k,"propTypes",{project:m.default.object.isRequired,screensCount:m.default.number.isRequired,toolbarActiveItem:m.default.string.isRequired,isDemo:m.default.bool})},rj4U:function(e,t,n){e.exports={"sub-toolbar":"_1lHJrguhCEQomzI0fKyRuD","select-input":"_3UQjksfyW2n5lPbsPnEgJv"}},rtgd:function(e,t,n){e.exports={"preview-toolbar":"_2GvcxT6MMVgPVqZ4pTagSW"}},rwIS:function(e,t,n){e.exports={"guide-button":"_30xMHfnBUgdhrZI7AsHGRs"}},tBsX:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),Object.defineProperty(t,"saga",{enumerable:!0,get:function(){return s.default}}),t.reducers=t.default=void 0
var r=a(n("MVZn")),i=n("ANjH"),o=n("/MKj"),l=a(n("xx4x")),s=a(n("7bR1")),c=a(n("eNKG")),u=a(n("ee4a")),d=n("Kkl0"),f=(0,i.combineReducers)((0,r.default)({},c.default,u.default))
t.reducers=f
var p=(0,o.connect)(function(e){var t=e.container,n=t.layers,a=t.common.keyFlags.isSpaceDown,r=t.previewSetting,i=r.toolbarActiveItem,o=r.isSelectLayer,l=r.isShowColorPicker,s=n.activeLayerID,c=n.resourceByScreen[n.visibilityScreenID]||{},u=c.isFetching,d=void 0===u||u,f=c.error
return{isActive:"inspect"==i,isSpaceDown:a,isSelectLayer:o,isShowColorPicker:l,isFetching:d,activeLayerID:s,error:void 0===f?"":f}},function(t){return{requestSelectLayer:function(e){t((0,d.requestSelectLayer)(e))},handleShowlayerInfo:function(e){t({type:"reducer:preview-toolbar:update",payload:{isSelectLayer:e}})}}})(l.default)
t.default=p},tRkt:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("43RC")),m=r(n("6gQ3")),v=n("oose"),g=r(n("zgSj")),y=n("1iCU"),b=n("/Mon"),S=function(e){function t(e){var n
return(0,i.default)(this,t),n=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(n),"toggleMinimized",function(e){var t=n.props.toolbarActiveItem
n.setState({isMinimized:e}),MB.event("preview","".concat(y.TOOLBAR_TRAKING_CONFIG[t],",点击了").concat(e?"收起":"展开","列表"))}),n.state={isMinimized:MB.isUIChina()||MB.isForum()},n}return(0,u.default)(t,e),(0,o.default)(t,[{key:"render",value:function(){var e=this.props,t=e.isLayerPanelShow,n=e.isCommentPanelShow,a=e.isScreenPanelShow,r=this.state.isMinimized
if(!(t||n||a))return null
var i=a?240:260
return p.default.createElement(b.StyledRightPane,{id:"mb-preview-rightpane",style:{width:r?0:i}},a&&p.default.createElement(p.default.Fragment,null,p.default.createElement("div",{className:"preview-panel-wrapper"},p.default.createElement(m.default,null)),p.default.createElement(h.default,{placement:"left",isMinimized:r,onClick:this.toggleMinimized})),t&&p.default.createElement(g.default,null),n&&p.default.createElement(v.CommentContainer,null))}}]),t}(p.PureComponent)
t.default=S,(0,d.default)(S,"propTypes",{toolbarActiveItem:f.default.string,isScreenPanelShow:f.default.bool,isLayerPanelShow:f.default.bool,isCommentPanelShow:f.default.bool})},tajm:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.patchGlobalAutoSaverPusher=void 0
var p=a(n("o0o1")),h=a(n("yXPU")),m=n("Saem"),v=n("Vk5q"),g=n("iKZC"),y=n("ycqN"),b=n("3caq"),S=n("Clcl"),w=window.MB
t.patchGlobalAutoSaverPusher=function(){var n,t,e=(0,g.createAutoSaveQueue)({delay:2e4,onError:(t=(0,h.default)(p.default.mark(function e(t){return p.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return(0,S.REPORT_ERROR)(t,"[AutoSaveQueue] unhandled error",r()),e.next=3,(0,y.SAVE_NUKE_SEQUENCE)(t,t.status)
case 3:case"end":return e.stop()}},e)})),function(e){return t.apply(this,arguments)}),doSave:(n=(0,h.default)(p.default.mark(function e(t,n){var a
return p.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return a=(0,v.processSaveQueue)(t),e.next=3,(0,g.doSaveWithSocketAndFallback)({setSavingState:n,getAutoSaveQueueState:r,saveChunkList:(0,m.arraySplitChunk)(a,64),saveQueueLength:a.length,getSaveItemInfo:v.getSaveItemInfo,isSocketAvailable:function(){return w.Pusher.getIsSocketConnected()},doSocketBatchSave:v.doSocketBatchSave,onSocketError:v.onSocketError,doFallbackSaveItem:v.doFallbackSaveItem,onFallbackError:v.onFallbackError})
case 3:case"end":return e.stop()}},e)})),function(e,t){return n.apply(this,arguments)})}),r=e.getState,a=e.getIsEmpty,i=e.getIsSaving,o=e.getDelay,l=e.setDelay,s=e.add,c=e.addEventListener,u=e.filterSaveQueue,d=e.triggerSave,f=e.afterCurrentSave
c("beforesave",function(){w.setSaving&&w.setSaving(!0)}),c("aftersave",function(){w.currentProject&&(w.currentProject.timestamp=String(.001*Date.now()),w.currentProject.updated_at=(new Date).toISOString(),w.currentProject.lsave(!1)),w.setSaving&&w.setSaving(!1),w.renderCoWorkers&&w.renderCoWorkers()}),w.Pusher=(0,b.createWorkspacePusher)({filterStaleData:function(o){var l=new Set,s=[]
return u(function(e){var t=e.record,n=t.cid,a=t.mtime,r=o[n],i=!r||r<a
return i?l.add(n):s.push(e),i}),{remoteStaleCidSet:l,localStaleDataList:s}}}),w.AutoSaver={getState:r,getIsEmpty:a,getIsSaving:i,getDelay:o,setDelay:l,triggerSave:d,afterCurrentSave:f,add:function(e){var t=e.record,n=e.isDelete,a=void 0!==n&&n
t.mtime=w.Pusher.getSocketTimestamp(),s({record:t,isDelete:a})}},(0,y.PATCH_AUTO_SAVE_RELATED)()}},tfo6:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("J4zp")),l=r(n("lwsE")),i=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),p=r(n("17x9")),h=a(n("q1tI")),m=r(n("DKAG")),v=r(n("lwmc")),g=function(e){function t(e){var i
return(0,l.default)(this,t),i=(0,s.default)(this,(0,c.default)(t).call(this,e)),(0,f.default)((0,u.default)(i),"handleExpand",function(e,t){e.stopPropagation()
var n=i.state.collapseKeySet,a=t.cid,r=new Set(n)
n.has(a)?r.delete(a):r.add(a),i.setState({collapseKeySet:r})}),(0,f.default)((0,u.default)(i),"handleActivate",function(e,t){var n=i.props,a=n.activeCid,r=n.dispatch
e.stopPropagation(),a===t.cid?i.handleExpand(e,t):(r({type:"entry:sync-runner:set-screen",payload:{cid:t.cid}}),r({type:"preview:set:canvas:offset",payload:{offset:{x:0,y:0}}}))}),(0,f.default)((0,u.default)(i),"handleKeyDown",function(e){(e.ctrlKey||e.metaKey)&&(186==e.keyCode&&(e.preventDefault(),i.resetExpandAll()),222==e.keyCode&&(e.preventDefault(),i.closeExpanedAll()))}),(0,f.default)((0,u.default)(i),"resetExpandAll",function(){i.setState({collapseKeySet:new Set})}),(0,f.default)((0,u.default)(i),
"closeExpanedAll",function(){var e=(i.props.screenTreeData||{}).childListMap,r=new Set
Object.entries(e).map(function(e){var t=(0,o.default)(e,2),n=t[0],a=t[1]
Array.isArray(a)&&a.length&&r.add(n)}),i.setState({collapseKeySet:r})}),i.state={collapseKeySet:new Set},i.treeProps={renderItem:e.renderCommentIcon,handleScreenItemActions:{handleExpand:i.handleExpand,handleActivate:i.handleActivate}},i}return(0,d.default)(t,e),(0,i.default)(t,[{key:"componentDidUpdate",value:function(e){if(e.activeCid!==this.props.activeCid){var t=Screen.find(this.props.activeCid)
if(t.parent_cid){var n=this.state.collapseKeySet,a=new Set(n)
n.has(t.parent_cid)&&a.delete(t.parent_cid),this.setState({collapseKeySet:a})}}}},{key:"render",value:function(){var e=this.props,t=e.activeCid,n=e.isSearching,a=e.screenTreeMap,r=e.screenDataMap
return h.default.createElement(h.default.Fragment,null,h.default.createElement(v.default,{collapseKeySet:this.state.collapseKeySet,activeCid:t,isSearching:n,screenTreeMap:a,screenDataMap:r,treeProps:this.treeProps}),h.default.createElement(m.default,{target:document,onKeyDown:this.handleKeyDown}))}}]),t}(h.PureComponent)
t.default=g,(0,f.default)(g,"propTypes",{activeCid:p.default.string,isSearching:p.default.bool,screenTreeData:p.default.object,screenTreeMap:p.default.object,screenDataMap:p.default.object,renderCommentIcon:p.default.func,dispatch:p.default.func})},tjcH:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=a(n("yLV6")),l=window.Shake,s=function(){function e(){(0,r.default)(this,e),this.hightTimer=null}return(0,i.default)(e,[{key:"init",value:function(e){var t=this,n=new o.default(e,{touchAction:"auto",inputClass:MB.isMobile()?o.default.TouchInput:null})
n.get("swipe").set({direction:o.default.DIRECTION_ALL,velocity:.05,threshold:50}),n.on("swipeleft",function(e){t.prepareJump(e,"left")}),n.on("swiperight",function(e){t.prepareJump(e,"right")}),n.on("swipeup",function(e){t.prepareJump(e,"up")}),n.on("swipedown",function(e){t.prepareJump(e,"down")}),n.on("press",function(e){t.prepareJump(e,["hold","longpress"])}),n.on("tap",function(e){1===e.tapCount&&t.prepareJump(e,["tap","click"]),2===e.tapCount&&(MB.runner.eventBucket.resetCoolDown(),t.prepareJump(e,[
"dtap","dbclick"]))}),new l({threshold:15}).start(),window.addEventListener("shake",function(e){t.prepareJump(e,"shake")},!1),this.hammertime=n}},{key:"prepareJump",value:function(e,t){var n=MB.runner,a=n.eventBucket,r=n.runnerUtil,i=n.timerHandler,o=n.currentMenu
if(!r.getIsImmersive()){var l=i.getIsPageTimerFired()
if(a.isCoolDown()&&!l){var s,c=$(e.target).closest(".clickable"),u=$(e.target).closest(".ppanel")
if(s=t.includes("shake")?o?$("#pscreen".concat(o)):$(".pcanvas.active"):$(e.target).closest(".pcanvas"),o&&s.data("cid")!==o)return MB.runner.closeMenu()
if(u.length){if(this.panelEventHandler(e,t))return}else if(c.length){var d=Link.find(c.attr("data-link_cid"))
if(d&&t.includes(d.gesture))return MB.runner.j(d)}var f=s.data("cid"),p=Screen.find(f)
if(p){var h=[]
Link.records.forEach(function(e){e.widget_cids===p.cid&&e.sourcestate_cid===p.state_cid&&t.includes(e.gesture)&&h.push(e)})
var m=p.globalLinks(p.state_cid).filter(function(e){return t.includes(e.gesture)})
m.length?MB.runner.j(m[0]):t.includes("hold")&&MB.messageBucket&&!window.parent.webkit?MB.messageBucket.send("settings"):MB.runner.runnerUtil.getIsHighlight()&&this.highlightClickables()}}}}},{key:"panelEventHandler",value:function(e,a){var t=$(e.target).closest(".clickable"),n=$(e.target).closest(".ppanel"),r=n.find(".pstate.active"),i=n.data("cid"),o=Panel.find(i)
if(t.length){var l=Link.find(t.attr("data-link_cid"))
if(!l)return!1
if("prev"===l.target_cid)return MB.runner.j(l),!0
if(a.includes(l.gesture)){if(n[0]===t[0])MB.runner.j(l)
else{var s=Screen.find(l.target_cid)
if(s&&s.project_cid!==o.template_cid)MB.runner.j(l)
else{if(MB.runner.timerHandler.getIsPanelTimerFired(o.cid))return!1
l.targetstate_cid?MB.runner.chameleonTransition(i,l):MB.runner.panelScreenTransition(o.cid,l)}}return!0}}if(MB.runner.timerHandler.getIsPanelTimerFired(o.cid))return!1
var c=Screen.find(r.data("cid"))
if(!c)return!1
var u=null
return c.cwidgets().forEach(function(e){if(!u&&"pg"===e.name){var t=Widgetstate.find(c.state_cid+e.cid)||e,n=Link.find(t.link_cids)
n&&a.includes(n.gesture)&&(n.targetstate_cid?MB.runner.chameleonTransition(i,n):MB.runner.panelScreenTransition(o.cid,n),u=!0)}}),!!u}},{key:"highlightClickables",value:function(){var e=$(".pcanvas.active .region")
e.show(),$(".pcanvas.active .pg").css({display:"flex",opacity:.8}),this.hightTimer=setTimeout(function(){e.hide(),$(".pcanvas.active .pg").css("opacity","0").hide()},400)}},{key:"setupPageGesture",value:function(e){var t=[]
e.clinks().forEach(function(e){"left"!==e.gesture&&"right"!==e.gesture||-1===t.indexOf("pan-y")&&t.push("pan-y"),"up"!==e.gesture&&"down"!==e.gesture||-1===t.indexOf("pan-x")&&t.push("pan-x")})
var n=t.length?t.join(" "):"auto"
this.hammertime.touchAction.actions=n,$(".pcanvas.active .widgets").css("touch-action",n)}}]),e}()
t.default=s},uW4e:function(e,t,n){"use strict"
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var a=n("WVP6"),r=n("Ehhz").MODEL_OPERATION_MAP.CommentThread,i=(0,a.createStateStore)([]),o=i.getState,l=i.setState,s=i.wrapEntry,c=function(i,o){return s(function(e,t,n){var a=t.dispatch,r=n&&n.payload
a({type:"reducer:comment-threads:update",payload:i(e,r,o)})})},u={entryMap:{"comment-threads:refresh":c(r.refreshStateList,!1),"comment-threads:save":c(r.saveState,!1),"comment-threads:add":c(r.addState,!1),"comment-threads:add-local":c(r.addState,!0),"comment-threads:update":c(r.updateState,!1),"comment-threads:update-local":c(r.updateState,!0),"comment-threads:delete":c(r.deleteState,!1),"comment-threads:delete-local":c(r.deleteState,!0)},getState:o,setState:l}
t.default=u},udLg:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=a(n("Aq2W")),l=a(n("YwNm")),s=a(n("tjcH")),c=a(n("wmEP")),u=function(){function e(){(0,r.default)(this,e),this.eventBucket=new o.default,this.runnerUtil=new l.default,this.eventHandler=new s.default,this.timerHandler=new c.default,this.clearCallbackBucket={},this._bindWindowEvent()}return(0,i.default)(e,[{key:"_bindWindowEvent",value:function(){var e=this
MB.isMobile()&&window.addEventListener("message",function(e){try{if("back"===JSON.parse(e.data).event)1===MB.webpackInterface.store.getState().container.runner.history.length&&MB.messageBucket?MB.messageBucket.send("exit"):MB.webpackInterface.store.dispatch({type:"entry:runner:back-to-prev-page",payload:{transition:{name:"none",delay:0,duration:0}}})}catch(e){}},!1),MB.isMobile()&&(window.onorientationchange&&window.addEventListener("orientationchange",function(){e.reload()}),window.addEventListener(
"resize",function(){"INPUT"!==document.activeElement.tagName&&e.reload()}))}},{key:"init",value:function(e,t){var n=this
MB.event("ga-0","send","pageview",{page:"/workspace/app/preview"}),console.log("runner - init: ",e,t),$("#app").show(),e.setup(),this.eventHandler.init(document.querySelector("#app")),this.currentScreen=this.currentMenu=null,MB.webpackInterface.store.dispatch({type:"runner:generate:widgets-query-map"}),MB.webpackInterface.store.dispatch({type:"entry:runner:init:home-screen",payload:{activeCid:t.cid}})
var a=setTimeout(function(){if(MB.webpackInterface.store.dispatch({type:"entry:runner:activate:screen",payload:{screenCid:t.cid}}),$("#simulator .splash").hide(),$("#splash").hide(),MB.webpackInterface.checkLocationHash(),MB.messageBucket){MB.messageBucket.send("ready",JSON.stringify(MB.currentProject.cscreens()))
var e=setTimeout(function(){MB.messageBucket.send("ready",JSON.stringify(MB.currentProject.cscreens()))},5e3)
n.clearCallbackBucket.redundantReady=function(){return clearTimeout(e)}}},1e3)
this.clearCallbackBucket.init=function(){return clearTimeout(a)}}},{key:"clear",value:function(){Object.values(this.clearCallbackBucket).forEach(function(e){return e()}),this.runnerUtil.clear(),this.timerHandler.clear(),MB.webpackInterface.store.dispatch({type:"runner:reset:state"})}},{key:"closeMenu",value:function(e){MB.webpackInterface.store.dispatch({type:"entry:runner:back-to-prev-page",payload:{callback:e}})}},{key:"j",value:function(e){if(e&&e.target_cid!==this.runnerUtil.getCurrentScreen().cid){
this.timerHandler.clear()
var t,n=e.target_cid
if(this.currentMenu)n===this.currentScreen?this.closeMenu():e.targetstate_cid?this.stateTransition(e):this.closeMenu((t=this,function(){return t.j(e)}))
else switch(e.link_type){case Link.TYPE.screen_link:this.screenTransition(e)
break
case Link.TYPE.state_link:this.stateTransition(e)
break
case Link.TYPE.panel_link:var a=Panel.find(e.target_cid)
a.multi_states?this.chameleonTransition(a.cid,e):this.panelScreenTransition(a.cid,e)
break
default:console.error("Unknown Link Type",e)}}}},{key:"screenTransition",value:function(e){var t={name:e.transition,delay:1e3*parseFloat(e.ani_delay),duration:1e3*parseFloat(e.ani_duration),offset:/drawer|menu/.test(e.transition)?e.menu_offset:100},n=e.target_cid
"prev"===n?(console.log("runner - screenTransition: 跳转到上一页"),MB.webpackInterface.store.dispatch({type:"entry:runner:back-to-prev-page",payload:{transition:t}})):(console.log("runner - screenTransition: 跳转到页面: ",Screen.find(n).name),Screen.find(n).orient()!==this.runnerUtil.getCurrentScreen().orient()?MB.webpackInterface.store.dispatch({type:"entry:runner:activate:screen",payload:{screenCid:n,resetTargetScreen:e.reset,transition:void 0}}):MB.webpackInterface.store.dispatch({
type:"entry:runner:activate:screen",payload:{screenCid:n,resetTargetScreen:e.reset,transition:t}}))}},{key:"stateTransition",value:function(e){console.log("runner - stateTransition",e)
var t={delay:1e3*parseFloat(e.ani_delay),duration:1e3*parseFloat(e.ani_duration)}
MB.webpackInterface.store.dispatch({type:"entry:runner:activate:screen-state",payload:{screenCid:e.screen_cid,stateCid:e.targetstate_cid,transition:t}})}},{key:"panelScreenTransition",value:function(e,t){console.log("runner - panelScreenTransition: ",e,t)
var n={name:["leftmenu","rightmenu","leftdrawer","rightdrawer"].includes(t.transition)?"none":t.transition,delay:1e3*parseFloat(t.ani_delay),duration:1e3*parseFloat(t.ani_duration),offset:/drawer|menu/.test(t.transition)?t.menu_offset:100}
MB.webpackInterface.store.dispatch({type:"entry:runner:activate:panel-screen",payload:{panelCid:e,panelScreenCid:t.target_cid,transition:n}})}},{key:"chameleonTransition",value:function(e,t){var n=t.targetstate_cid,a=Panel.find(e).ct().homeScreen()
if(a.state_cid!==n){console.log("runner - chameleonTransition: ",n),this.timerHandler.resetPanelTimerFlag(e),a.setState(n,!0)
var r={delay:1e3*parseFloat(t.ani_delay),duration:1e3*parseFloat(t.ani_duration)}
MB.webpackInterface.store.dispatch({type:"entry:runner:update:chameleon",payload:{chameleonCid:e,stateCid:n,transition:r}})}}},{key:"donePanelScreenTransition",value:function(e,t){console.log("runner - donePanelScreenTransition: ",e,t)
var n=document.querySelector("#state"+e+t+"p"),a=Panel.find(e)
this.timerHandler.resetPanelTimerFlag(a.cid),n.offsetParent&&(this.setupPanelWebPage($(n)),this.timerHandler.setupPanelTimers(a,t))}},{key:"doneTransition",value:function(e){console.log("runner - doneTransition: ",e)
var t=Screen.find(e)
this.timerHandler.setupPageTimers(t),this.setupWebpage(t),MB.isStandAlone()&&this.runnerUtil.setupStatusBar(t),MB.isAndroid()&&this.eventHandler.setupPageGesture(t),this.timerHandler.resetPageTimerFlag(),MB.currentScreen=t,MB.webpackInterface.updateCurrentScreenRunner(t),this.runnerUtil.renderScrollbar(t.cid)
var n=MB.isMobile()||MB.isEmbedded()||!this.runnerUtil.getIsScreenExpanded()
this.runnerUtil.toggleScrollBar(n),setTimeout(function(){MB.webpackInterface.store.dispatch({type:"entry:runner:preload:screens"})},10)}},{key:"reload",value:function(){console.log("runner - reload")
var e=this.runnerUtil.getCurrentScreen()
MB.webpackInterface.store.dispatch({type:"entry:runner:reload:screen",payload:{activeCid:e.cid}}),this.runnerUtil.renderScrollbar(e.cid),this.runnerUtil.resetScrollState()}},{key:"setupWebpage",value:function(e){var i=this
e.cpanels().forEach(function(e){$(".pcanvas [data-cid="+e.cid+"]").each(function(e,t){var n=$(t).find(".state.active")
i.setupPanelWebPage(n)})}),e.cwidgets().forEach(function(r){"webpage"===r.name&&$(".pcanvas [data-cid="+r.cid+"]").each(function(e,t){var n=$(t).find(".iframe")[0],a=r.text?r.text.replace(/&amp;/g,"&"):"about:blank"
i.runnerUtil.setObjectUrl(n,a)})})}},{key:"setupPanelWebPage",value:function(n){var a=this
Screen.find(n.data("cid")).cwidgets().forEach(function(e){if("webpage"===e.name&&e.text){var t=n.find("[data-cid="+e.cid+"]")
a.runnerUtil.setObjectUrl(t.find(".iframe")[0],e.text.replace(/&amp;/g,"&"))}})}}]),e}()
t.default=u},v8PR:function(e,t,n){},vRqJ:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:i,t=1<arguments.length?arguments[1]:void 0,n=t.type,a=t.payload
switch(n){case"reducer:artboards:success":return(0,r.default)({},e,a)
case"reducer:artboards:fail":return(0,r.default)({},e,a,{error:!0})
default:return e}}
var r=a(n("MVZn")),i={artboards:[],error:!1}},vbsp:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.StyledRadioLine=void 0
var r=a(n("vOnD")).default.ol.withConfig({displayName:"style__StyledRadioLine",componentId:"sc-15893ui-0"})(["display:flex;justify-content:center;height:100%;align-items:center;background:",";color:#7d8694;border-radius:2px;overflow:hidden;text-align:center;border:",";&.radio-line{height:22px;margin-bottom:14px;}.check-line{&.active{background:",";}}&.quick-radius{margin-bottom:0;li:first-child{border-right:",
";}}.radio-option{flex:1;display:flex;width:100%;height:100%;justify-content:center;align-items:center;position:relative;cursor:pointer;.radio-content{display:flex;justify-content:center;align-items:center;position:relative;}.move-cube{&.active{position:absolute;left:0;top:0;width:100%;height:100%;border-left:1px solid ",";border-right:1px solid ",";background:",
";transition:transform 0.2s ease-in-out;}}.main{fill:#7d8694;}.secondary{fill:#c8cdd0;}&.active{color:#298df8;cursor:default;.main{fill:#298df8;}.svg-icon{.secondary{fill:rgba(41,141,248,0.4);}}}&.disabled{color:#c8cdd0;background-color:#f7f7f7;cursor:not-allowed;}&:hover:not(.disabled){color:#298df8;.main{fill:#298df8;}.svg-icon{.secondary{fill:rgba(41,141,248,0.4);}}}}&.disabled{.radio-option{color:#c8cdd0;cursor:not-allowed;svg:only-child,.main{fill:#c8cdd0;}&:hover{color:#c8cdd0;}}.move-cube{&.active{background:"
,";border-left:transparent;border-right:transparent;}}}"],function(e){return e.theme.radioLine.bg},function(e){return e.theme.radioLine.border},function(e){return e.theme.radioLine.active_bg},function(e){return e.theme.radioLine.border},function(e){return e.theme.radioLine.border_color},function(e){return e.theme.radioLine.border_color},function(e){return e.theme.radioLine.active_bg},function(e){return e.theme.radioLine.bg})
t.StyledRadioLine=r},veUc:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.transformLayersFormat=void 0
var d=a(n("MVZn")),u=a(n("RIqP")),f=a(n("SA+Z")),p=n("0k54"),r=n("QDPf")
t.transformLayersFormat=function(e){var t=(0,f.default)(e),n=t[0],a=t.slice(1),r={childrenLayers:[]},i={},o=[],l=[]
a.forEach(function(e){var t=e.id,n=e.panel_cid
"artboard-base"===t?Object.assign(r,e):"number"==typeof t?r.childrenLayers.push(e):n?i[n]?i[n].push(e):i[n]=[e]:"panel"===e.name?o.push(e):l.push(e)}),o.forEach(function(e){return e.childrenLayers=i[e.cid]})
var s=r.childrenLayers.length?[r]:[],c=[].concat(s,o,(0,u.default)(h(l))).sort(function(e,t){return e.z-t.z||e.timestamp-t.timestamp})
return[n].concat((0,u.default)(c))}
var h=function(e){if(0===e.length)return[]
var t=e[0].screen_cid
return(0,r.generateTreeData)(e.map(function(e){return new Widget(e)}),t).widgetTreeData.children.map(function(e){return i(e)})},i=function t(e){var n=e.cid,a=e.type,r=e.widget,i=e.children
if("widget"===a)return r
if("group"===a){var o=(0,p.getTreeBoundingRect)(e),l=o.minX,s=o.minY,c=o.maxX,u=o.maxY
return(0,d.default)({},r,{id:n,width:c-l,height:u-s,top:s,left:l,childrenLayers:i.map(function(e){return t(e)})})}}},vmbo:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("PJYZ")),d=r(n("7W2i")),f=r(n("lSNA")),i=r(n("17x9")),b=a(n("q1tI")),S=r(n("TSYQ")),w=n("/5+U"),E=n("l0oT")
n("zZYZ")
var p=function(e){function i(){var e,r;(0,o.default)(this,i)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return r=(0,s.default)(this,(e=(0,c.default)(i)).call.apply(e,[this].concat(n))),(0,f.default)((0,u.default)(r),"onMouseEnter",function(e){-1!==r.props.activeLayerID&&r.props.enterLayer(r.props.layer.id)}),(0,f.default)((0,u.default)(r),"onMouseLeave",function(e){-1!==r.props.activeLayerID&&r.props.enterLayer(-1)}),(0,f.default)((0,u.default)(r),"handleClick",function(){var e=r.props,t=e.requestSelectLayer,n=e.layer.id,a=e.handleShowlayerInfo
t(n),a(!0)}),r}return(0,d.default)(i,e),(0,l.default)(i,[{key:"render",value:function(){var e=this.props,t=e.layer,n=e.activeLayerID,a=e.enteredLayerID,r=e.unit,i=e.ratio,o=t.id,l=t.src_width,s=t.src_height,c=t.rotation||0,u=o===n,d=o===a||-1===a,f=(0,S.default)("Layer",{"is-active":u,"is-focus":d}),p=t.kind?l:l*(0,E.cos)(c)+s*(0,E.sin)(c),h=t.kind?s:l*(0,E.sin)(c)+s*(0,E.cos)(c),m=(0,w.adapterScreen)(p,i),v=(0,w.adapterScreen)(h,i),g=t.kind?(0,w.adapterScreen)(t.origin_width||l,i):(0,w.adapterScreen)(l,i),
y=t.kind?(0,w.adapterScreen)(t.origin_height||s,i):(0,w.adapterScreen)(s,i)
return b.default.createElement("div",{className:f,"data-width":"".concat(m).concat(r),"data-height":"".concat(v).concat(r),"data-lid":o,onClick:this.handleClick,onMouseEnter:this.onMouseEnter,onMouseLeave:this.onMouseLeave},u&&b.default.createElement("span",{className:"LayerCorner left top"}),u&&b.default.createElement("span",{className:"LayerCorner left bottom"}),u&&b.default.createElement("span",{className:"LayerCorner right top"}),u&&b.default.createElement("span",{className:"LayerCorner right bottom"}),
u&&0!==c&&b.default.createElement("span",{className:"rect_info"},"".concat(g," x ").concat(y),"  ","".concat(c,"°")))}}]),i}(b.Component)
t.default=p,(0,f.default)(p,"propTypes",{layer:i.default.object,requestSelectLayer:i.default.func,enterLayer:i.default.func,handleShowlayerInfo:i.default.func,activeLayerID:i.default.oneOfType([i.default.number,i.default.string]),enteredLayerID:i.default.oneOfType([i.default.number,i.default.string]),unit:i.default.string,ratio:i.default.number})},wfO3:function(e,t,n){},wmEP:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var r=a(n("lwsE")),i=a(n("W8MJ")),o=a(n("f7BV")),l=function(){function e(){(0,r.default)(this,e),this.timerFired=!1,this.panelTimerMap={},this.timeoutBucket=new o.default}return(0,i.default)(e,[{key:"resetPageTimerFlag",value:function(){this.timerFired=!1}},{key:"getIsPageTimerFired",value:function(){return this.timerFired}},{key:"getIsPanelTimerFired",value:function(e){return this.panelTimerMap[e]}},{key:"resetPanelTimerFlag",value:function(e){this.panelTimerMap[e]=!1}},{key:"clear",value:function(){
this.timerFired=!1,this.panelTimerMap={},this.timeoutBucket.clear()}},{key:"setupPageTimers",value:function(e){var t=this,a=1<arguments.length&&void 0!==arguments[1]?arguments[1]:"default"
if(!MB.runner.runnerUtil.getIsImmersive()){this.timeoutBucket.clear()
var r=e.globalLinks(a)
e.citems().forEach(function(e){if("pg"!==e.name){var t="panel"===e.name?Panelstate.find(a+e.cid)||e:Widgetstate.find(a+e.cid)||e,n=Link.find(t.link_cids)
n&&r.push(n)}}),r.forEach(function(e){0<parseFloat(e.timer)&&(!e.targetstate_cid||e.sourcestate_cid===a)&&t.pageTimer(e)}),e.cpanels().forEach(function(e){t.setupPanelTimers(e,e.mainState().cid)})}}},{key:"setupPanelTimers",value:function(t,a){var n=this
if(this.timeoutBucket.clearTimeoutByKey(t.cid),this.panelTimerMap[t.cid]=!1,t.multi_states){var e=t.ct().homeScreen(),r=e.globalLinks(a)
e.cwidgets().forEach(function(e){if("pg"!==e.name){var t=Widgetstate.find(a+e.cid)||e,n=Link.find(t.link_cids)
n&&r.push(n)}}),r.forEach(function(e){0<parseFloat(e.timer)&&(!e.targetstate_cid||e.sourcestate_cid===a)&&(e.state_cid?n.pageTimer(e):n.panelTimer(e,t))})}else{var i=Screen.find(a)
i.clinks().forEach(function(e){0<parseFloat(e.timer)&&n.panelTimer(e,t)}),Link.findAllByAttribute("state_cid",i.cid).forEach(function(e){0<parseFloat(e.timer)&&n.pageTimer(e)})}}},{key:"pageTimer",value:function(e){var t=this
this.timeoutBucket.setTimeout(e.cid,function(){t.timerFired||(t.timerFired=!0,MB.runner.runnerUtil.getIsImmersive()||MB.runner.j(e))},1e3*parseFloat(e.timer))}},{key:"panelTimer",value:function(e,t){var n=this
this.timeoutBucket.setTimeout(t.cid,function(){n.timerFired||n.panelTimerMap[t.cid]||(n.panelTimerMap[t.cid]=!0,MB.runner.runnerUtil.getIsImmersive()||(e.targetstate_cid?MB.runner.chameleonTransition(t.cid,e):MB.runner.panelScreenTransition(t.cid,e)))},1e3*parseFloat(e.timer))}}]),e}()
t.default=l},xQM3:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.getScreenContainerStyle=function(e,t,n,a,r){var i
if(a){var o,l=Math.min(n.width,n.height),s=Math.max(n.width,n.height),c=Math.min(t.width,t.height),u=Math.max(t.width,t.height),d=e.width!==c,f=n.width>n.height,p=d!=f
i=d?(o=s/u,{width:u,height:Math.min(c,l/o),transform:"".concat(p?"translate(-100%) rotate(-90deg)":""," scale(").concat(o,")"),transformOrigin:p?"top right":"top left"}):(o=l/c,{width:c,height:Math.min(u,s/o),transform:"".concat(p?"translate(-100%) rotate(-90deg)":""," scale(").concat(o,")"),transformOrigin:p?"top right":"top left"})}else if(r)i={width:e.width,height:e.height}
else{var h="landscape"===e.orientation,m=t.width,v=t.height,g=h?[v,m]:[m,v],y=(0,w.default)(g,2),b=y[0],S=y[1]
i={width:b,height:S}}return i}
var w=a(n("J4zp"))},xUDz:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=a(n("RIqP")),l=a(n("lSNA")),r=n("/MKj"),i=n("/5+U"),s=a(n("o/90")),c=(0,r.connect)(function(e){var t=e.model,n=t.current,a=t.screens,r=e.container,i=r.previewSetting.isFullScreenMode,o=r.common.scale,l=n.screenCid,s=u(a,l),c=d(a,n.projectCid).childListMap
return{screen:s,isFullScreenMode:i,screenInOrder:f(c,"root"),scale:o}})(s.default)
t.default=c
var u=(0,i.immutableTransformCache)(function(e,t){return e.find(function(e){return e.cid===t})}),d=(0,i.immutableTransformCache)(function(e,r){var i={},o=(0,l.default)({},"root",[])
return e.forEach(function(e){if(e.project_cid===r){var t=e.cid,n=e.position,a=e.parent_cid||"root"
i[t]=e,void 0===o[a]&&(o[a]=[]),o[a].push({cid:t,position:n})}}),Object.values(o).forEach(function(e){return e.sort(function(e,t){return i[e.cid].position-i[t.cid].position})}),{rootCid:"root",nodeMap:i,childListMap:o}}),f=function a(r,e){var i=[]
return r[e].forEach(function(e){var t=e.cid
if(i.push(t),r[t]){var n=a(r,t)
i.push.apply(i,(0,o.default)(n))}}),i}},xV1f:function(e,r,t){(function(e){r.__esModule=!0,r.CLOCK_PER_SECOND=1e3,r.CLOCK_TO_SECOND=.001,r.getTimestamp=function(){return Math.floor(.001*Date.now())},r.setTimeoutAsync=function(t){return void 0===t&&(t=0),new Promise(function(e){return setTimeout(e,t)})}
var t=e.requestAnimationFrame?[e.requestAnimationFrame,e.cancelAnimationFrame]:[function(e){return setTimeout(e,1e3/60)},clearTimeout],n=t[0],a=t[1]
r.cancelFrameUpdate=a,r.requestFrameUpdate=n,r.createTimer=function(e){var t=e.func,n=e.delay,a=e.queueTask,r=void 0===a?setTimeout:a,i=e.cancelTask,o=void 0===i?clearTimeout:i,l=null,s=function e(){l&&(l=r(e,n),t())},c=function(){l||(l=r(s,n))},u=function(){l&&(o(l),l=null)}
return{start:c,stop:u,isActive:function(){return Boolean(l)},getDelay:function(){return n},setDelay:function(e){e!==n&&(n=e,u(),c())}}}}).call(this,t("yLpj"))},xn7q:function(e,t,n){e.exports={previewPanelLayer:"McoEqJKUUcz4r7-DS9tH",layerInfo:"CjM2RPzWdeKb7pXpcipsf"}},"xo+i":function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var s=a(n("lSNA")),r=n("/MKj"),i=a(n("h2Vm")),o=n("/5+U"),l=(0,r.connect)(function(e){return{screenTreeData:u(e.model.screens,e.model.current.projectCid),screenCommentThreadCountMap:c(e.model.commentThreads),currentScreenCid:e.model.current.screenCid,screenSearch:e.container.screens.screenSearch,layout:e.container.common.preference.layout}})(i.default)
t.default=l
var c=(0,o.immutableTransformCache)(function(e){return e.reduce(function(e,t){return e[t.screen_cid]=(e[t.screen_cid]||0)+1,e},{})}),u=(0,o.immutableTransformCache)(function(e,r){var i={},o={},l=(0,s.default)({},"root",[])
return e.forEach(function(e){if(e.project_cid===r){var t=e.cid,n=e.position,a=e.parent_cid||"root"
i[t]=e,o[t]=String(e.name).toLowerCase(),void 0===l[a]&&(l[a]=[]),l[a].push({cid:t,position:n})}}),Object.values(l).forEach(function(e){return e.sort(function(e,t){return i[e.cid].position-i[t.cid].position})}),{rootCid:"root",nodeMap:i,childListMap:l,screenNameCidMap:o}})},"xtk/":function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var i=r(n("lwsE")),o=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("TSYQ")),m=r(n("8CMD")),v=function(e){function t(e){var a
return(0,i.default)(this,t),a=(0,l.default)(this,(0,s.default)(t).call(this,e)),(0,d.default)((0,c.default)(a),"setElementRef",function(e){return a.$elem=e}),(0,d.default)((0,c.default)(a),"updateIsVisible",function(){a.setState({isVisible:a.isInBoundingClientRect()})}),(0,d.default)((0,c.default)(a),"handleClick",function(e){e.stopPropagation()
var t=a.props,n=t.screen;(0,t.onActivate)(n.cid)}),a.state={isVisible:!1},a}return(0,u.default)(t,e),(0,o.default)(t,[{key:"componentDidMount",value:function(){this.props.containerRect&&this.updateIsVisible()}},{key:"componentDidUpdate",value:function(e,t){var n=this.isInBoundingClientRect()
if(!e.containerRect&&this.props.isActive&&!n){var a=this.$elem.getBoundingClientRect()
this.props.scrollIntoView(a)}this.updateIsVisible()}},{key:"isInBoundingClientRect",value:function(){var e=this.props.containerRect
if(!e||!this.$elem)return!1
var t=this.$elem.getBoundingClientRect()
return t.bottom>e.top&&t.top<e.bottom}},{key:"render",value:function(){var e=this.props,t=e.projectToken,n=e.screen,a=e.isEditing,r=e.isHover,i=e.version,o=e.isActive,l=e.treeProps,s=l.renderItem,c=l.renderSpan,u=void 0===c?g:c,d=n.cid,f=this.state.isVisible
return p.default.createElement("li",{className:(0,h.default)("thumbnail-item",{active:o}),onClick:this.handleClick},p.default.createElement("div",{ref:this.setElementRef,className:(0,h.default)("image-wrapper",{hover:r})},s&&s(n),p.default.createElement(m.default,{projectToken:t,screenCid:d,version:i,isVisible:f})),u(n,a))}}]),t}(p.PureComponent);(t.default=v).propTypes={screen:f.default.object,version:f.default.string,isEditing:f.default.bool,isHover:f.default.bool,projectToken:f.default.string,
containerRect:f.default.object,isActive:f.default.bool,onActivate:f.default.func,scrollIntoView:f.default.func,treeProps:f.default.object},v.defaultProps={treeProps:{}}
var g=function(e){return p.default.createElement("span",{className:"screen-name editable-span"},e.name)}},xx4x:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var o=r(n("lwsE")),i=r(n("W8MJ")),l=r(n("a1gu")),s=r(n("Nsbk")),c=r(n("PJYZ")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=r(n("DKAG")),m=r(n("ZS4k")),v=r(n("d89S")),g=function(e){function r(){var e,i;(0,o.default)(this,r)
for(var t=arguments.length,n=new Array(t),a=0;a<t;a++)n[a]=arguments[a]
return i=(0,l.default)(this,(e=(0,s.default)(r)).call.apply(e,[this].concat(n))),(0,d.default)((0,c.default)(i),"checkIfNeedHideLayer",function(e){var t=i.props,n=t.isSpaceDown,a=t.requestSelectLayer,r=t.handleShowlayerInfo
!n&&e.target.contains(document.getElementById("simulator-container"))&&(a(-1),r(!1))}),i}return(0,u.default)(r,e),(0,i.default)(r,[{key:"render",value:function(){var e=this.props,t=e.isFetching,n=e.error,a=e.isActive,r=e.isSelectLayer,i=e.isShowColorPicker,o=e.activeLayerID
if(!a)return null
if(t)return null
if(n)return null
var l=-1!==o&&!i
return p.default.createElement("div",null,p.default.createElement(m.default,null),l&&p.default.createElement(v.default,null),r&&p.default.createElement(h.default,{target:document,onClick:this.checkIfNeedHideLayer}))}}]),r}(p.PureComponent);(t.default=g).propTypes={isActive:f.default.bool,isFetching:f.default.bool,isSpaceDown:f.default.bool,isSelectLayer:f.default.bool,isShowColorPicker:f.default.bool,activeLayerID:f.default.oneOfType([f.default.number,f.default.string]),requestSelectLayer:f.default.func,
handleShowlayerInfo:f.default.func,error:f.default.string}},yOnP:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=o
var s=a(n("MVZn")),c=a(n("o0o1")),u=n("oZtI"),d=n("S7Zs"),r=c.default.mark(o),i=c.default.mark(l),f=c.default.mark(p)
function o(){return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,u.all)([l()])
case 2:case"end":return e.stop()}},r)}function l(){return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,u.takeEvery)("reducer:artboards:init",p)
case 2:case"end":return e.stop()}},i)}function p(e){var t,n,a,r,i,o,l
return c.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,(0,u.select)()
case 2:if(t=e.sent,n=t.model,a=n.current.projectCid,r=n.screens,e.prev=4,i={},r.forEach(function(e){var t=e.width,n=e.height,a=e.cid
i[a]={width:t,height:n}}),a)return e.next=10,(0,u.call)(d.fetchArtboardsByProjectCid,a)
e.next=13
break
case 10:o=e.sent,0<(l=o.artboards).length&&l.forEach(function(e){var t=e.width,n=e.height,a=e.screen_cid
i[a]={width:t,height:n}})
case 13:return i={artboards:i},e.next=16,(0,u.put)({type:"reducer:artboards:success",payload:(0,s.default)({},i)})
case 16:e.next=23
break
case 18:return e.prev=18,e.t0=e.catch(4),console.log(e.t0.stack),e.next=23,(0,u.put)({type:"reducer:artboards:fail"})
case 23:case"end":return e.stop()}},f,null,[[4,18]])}},ycqN:function(e,t,n){"use strict"
var a=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.PATCH_AUTO_SAVE_RELATED=t.SAVE_NUKE_SEQUENCE=void 0
var r=a(n("o0o1")),i=a(n("yXPU")),o=n("xV1f"),l=n("XkTy"),s=n("Clcl"),c=window,u=c.$,d=c.MB,f=function(){var n=0<arguments.length&&void 0!==arguments[0]?arguments[0]:{}
return new Promise(function(e,t){(0,l.alertAsyncBlocked)(n).then(e),setTimeout(t,6e4)}).catch(function(){return setTimeout(function(){return(0,s.POST_REPORT)({type:"Error:alertAsyncBlocked:timeout",option:n})},0)})},p=function(){var t=(0,i.default)(r.default.mark(function e(t){var n,a=arguments
return r.default.wrap(function(e){for(;;)switch(e.prev=e.next){case 0:return n=1<a.length&&void 0!==a[1]?a[1]:-255,e.next=3,f({desc:I18N.unknown_error.replace(/%s/i,n),isHTML:!0})
case 3:return window.parent.location.reload(),d.event("zhuge","Workspace_ErrorMsg",{ErrorCode:"Save_Error"}),(0,s.NUKE)(t),e.next=8,(0,o.setTimeoutAsync)(36e5)
case 8:case"end":return e.stop()}},e)}))
return function(e){return t.apply(this,arguments)}}()
t.SAVE_NUKE_SEQUENCE=p
t.PATCH_AUTO_SAVE_RELATED=function(){(0,s.SETUP_REPORT_INTERVAL)({type:"AutoSaver:Socket",getReportObject:function(){return d.AutoSaver.getState()}}),window.onbeforeunload=function(){return d.AutoSaver.getIsEmpty()?void 0:d.isLegacyElectron()?!d.confirmAsync({title:I18N.warning,desc:I18N.data_lost_warning})||void 0:I18N.data_lost_warning},d.myXhr=u.ajaxSettings.xhr(),u.ajaxSettings.xhr=function(){return d.myXhr},u.ajaxSetup({timeout:6e4})}},yl0K:function(e){e.exports={
"// HOSTED_COMMERCIAL_FANGZHENG_LIST":"NOTE: this file is script generated, change should be made at 'fe/scripts/generateFontResource.js'",HOSTED_COMMERCIAL_FANGZHENG_LIST:[{family:"FZLanTingHei",label:"方正兰亭黑",typeList:["regular","light","bold"]},{family:"FZYuan",label:"方正圆体",typeList:["regular","light","bold"]},{family:"FZXinSong",label:"方正新书宋",typeList:["regular"]},{family:"FZKai",label:"方正楷体",typeList:["regular"]},{family:"FZGongYeHei",label:"方正工业黑",typeList:["regular"]},{family:"FZHanZhenGuangBiao",
label:"方正汉真广标",typeList:["regular"]},{family:"FZZongYi",label:"方正综艺体",typeList:["regular"]}],"// HOSTED_COMMON_LIST":"NOTE: this file is script generated, change should be made at 'fe/scripts/generateFontResource.js'",HOSTED_COMMON_LIST:[{family:"PingFangSC",label:"PingFang SC",limitedDevices:["iphone","ipad","apple_watch"],typeList:["regular","bold"]},{family:"SourceHanSansSC",label:"思源黑体",typeList:["regular","bold"]},{family:"SFUIText",label:"SF UI Text",limitedDevices:["iphone","ipad","apple_watch"],
typeList:["regular","bold"]},{family:"Roboto",label:"Roboto",typeList:["regular","bold"]}],"// WESTERN_COMMON_LIST":"NOTE: this file is script generated, change should be made at 'fe/scripts/generateFontResource.js'",WESTERN_COMMON_LIST:[{family:"Arial",label:"Arial",typeList:["regular","bold"]},{family:"Courier New",label:"Courier New",typeList:["regular","bold"]},{family:"Helvetica",label:"Helvetica",typeList:["regular","light","bold"]},{family:"Times New Roman",label:"Times New Roman",typeList:["regular"
,"bold"]}]}},zZYZ:function(e,t,n){},zgSj:function(e,t,n){"use strict"
var a=n("284h"),r=n("TqRt")
Object.defineProperty(t,"__esModule",{value:!0}),t.default=void 0
var v=r(n("MVZn")),i=r(n("pVnL")),o=r(n("lwsE")),l=r(n("W8MJ")),s=r(n("a1gu")),c=r(n("Nsbk")),u=r(n("7W2i")),d=r(n("lSNA")),f=r(n("17x9")),p=a(n("q1tI")),h=n("/MKj"),m=r(n("J2m7")),g=r(n("sxGJ")),y=n("RUem"),b=n("qOCw"),S=n("/5+U"),w=r(n("inTe")),E=r(n("xn7q")),k=function(e){function r(){var t
return(0,o.default)(this,r),(t=(0,s.default)(this,(0,c.default)(r).call(this))).getScrollLayerRef=function(e){return t.layerRef=e},t.state={error:!1},t}return(0,u.default)(r,e),(0,l.default)(r,[{key:"componentDidMount",value:function(){this.clipBoard=new g.default('[data-type="copy"]')}},{key:"componentWillUnmount",value:function(){this.clipBoard.destroy()}},{key:"componentWillReceiveProps",value:function(e){e.screenCid!=this.props.screenCid&&this.props.dispatch({type:"reducer:preview-toolbar:update",
payload:{isSelectLayer:!1}})}},{key:"componentDidUpdate",value:function(e){e.layer&&this.props.layer&&e.layer.id!=this.props.layer.id&&this.layerRef&&(this.layerRef.scrollTop=0)}},{key:"componentDidCatch",value:function(e){this.setState({error:!0}),console.error(e)}},{key:"render",value:function(){var e=this.props,t=e.isSelectLayer,n=e.layer,a=this.state.error
return p.default.createElement("div",{className:E.default.previewPanelLayer},n?p.default.createElement("div",{className:E.default.layerInfo,ref:this.getScrollLayerRef},a?p.default.createElement(r.Error,null):p.default.createElement(w.default,(0,i.default)({},this.props,{showGlobal:!t}))):p.default.createElement(y.Loading,null))}}]),r}(p.PureComponent);(0,d.default)(k,"Error",function(){return p.default.createElement("div",null,"Sorry!Error happend, Please refresh it")}),(0,d.default)(k,"propTypes",{
colorUnit:f.default.string.isRequired,isSelectLayer:f.default.bool.isRequired,unit:f.default.string.isRequired,ratio:f.default.number.isRequired,layer:f.default.object,screenCid:f.default.string,dispatch:f.default.func.isRequired})
var C=(0,h.connect)(function(e){var t=e.container,n=t.layers,a=n.activeLayerID,r=n.visibilityScreenID,i=n.resourceByScreen,o=t.previewSetting,l=e.model,s=l.current,c=s.screenCid,u=s.projectCid,d=l.projects,f=o.isSelectLayer,p=T(d,u).device,h=_(f,i,r,a),m=x(i,r,p)
return(0,v.default)({},o,{layer:h},m,{screenCid:c})})(k)
t.default=C
var x=(0,S.immutableTransformCache)(function(e,t,n){var a=[],r=[],i=[],o=[],l=e[t]
if(l){var s=l.layers,c=(0,b.sortScreenLayers)(s)
a=c.screenColor,o=c.globalText,r=l.documentColor,i=l.globalColor}return{screenColor:a,documentColor:r,globalColor:i,globalText:o}}),T=(0,S.immutableTransformCache)(function(e,t){return e.find(function(e){return e.cid===t})}),_=(0,S.immutableTransformCache)(function(e,t,n,a){var r=t[n]
if(!r||r.layers&&0==r.layers.length)return null
var i=r.layers
return e?(0,m.default)(i,function(e){return e.id===a}):(0,v.default)({},i[0])})},zy85:function(e,t,n){e.exports={"runner-control-panel":"_1X_2UmrkGlhWCjY4oDmJxO"}}},[[6,1,0]]])

//# sourceMappingURL=preview-1f75d39487a064049a64.js.map