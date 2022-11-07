#pragma once

#include <pgmspace.h>

#pragma region Brand
const char BRAND_CSS[] PROGMEM = R"=====(
:root{
	--main-bg-color: darkred;
	--main-text-color: #fff;
	--secondary-text-color: darkred;
	
}

.textCentered{ text-align: center; }

.qtrText{
	font-size: 1.25vmax;
	margin-inline: 0.5vw;
}

input[type="text" i] {
    padding: 0px;
}

.btnForm{
	color: #fff !important;
	height: 32px !important;
	margin-left:auto;
	margin-right:auto;
	display: flex !important;
	justify-content: center;
	align-items: center;
}

.btnForm:hover{
	color: #194268 !important;
}

.btnDisabled{
	opacity: 0.5;
}

#logo
{
	display: block;
	-moz-box-sizing: border-box;
	box-sizing: border-box;
	background: url('../Fig/logo.png') no-repeat;
    
    width: 128px;
    height: 128px;
	margin-top: -9px;
}

body { font-family: 'Nunito', sans-serif; color: var(--main-text-color); background-color: #777777; overflow-x: hidden; }
a:link, a:hover, a:active, a:focus, a:visited { text-decoration: none !important; }
* { outline: none; box-sizing: border-box !important; }
a:focus { outline: none !important; }

p {
	font-size: 14px;
	color: var(--main-text-color);
	font-weight: 300;
	margin-bottom: 0px;
}
	p strong { font-weight: 600; font-size: 16px; }

.remove-padding { padding: 0; }
.remove-right { padding-right: 0; }
.clearfix:before, .clearfix:after, .row:before, .row:after { content: '\0020'; display: block; overflow: hidden; visibility: hidden; width: 0; height: 0; } .row:after, .clearfix:after {clear: both; } .row, .clearfix {zoom: 1; } .clear {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 0; } .clear5 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 5px; } .clear10 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 10px; } .clear15 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 15px; } .clear20 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 20px; } .clear25 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 25px; } .clear30 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 30px; } .clear35 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 35px; } .clear40 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 40px; } .clear45 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 45px; } .clear50 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 50px; } .clear60 {clear: both; display: block; overflow: hidden; visibility: hidden; width: 0; height: 60px; } .lfloat {float: left } .rfloat {float: right }
.row { margin-bottom: 0; }

/* DEFAULT */

h2 {
	font-size: 34px;
	font-weight: 700;
	text-transform: uppercase;
	line-height: 44px;
	color: var(--main-text-color);
}
	h2 span { font-weight: 300; display: block; }

h3 {
	color: #236fb2;
	font-size: 40px;
	text-transform: uppercase;
	font-weight: 200;
	line-height: 44px;
	margin-bottom: 40px;
}
	h3 strong { font-weight: 600; }

h4 {
	font-size: 20px;
	color: var(--main-text-color);
	text-transform: uppercase;
	line-height: 24px;
	font-weight: 600;
	margin-bottom: 20px;
}

h4 i { color: #86a66b; margin-right: 20px; }

h5 {
	color: var(--secondary-text-color);
	font-size: 22px;
	font-weight: 700;
	margin-bottom: 15px;
    text-transform: uppercase;
    text-shadow: 1px 1px 2px gray;
}

h6 {
	color: #1a70b9;
	display: block;
	border-bottom: 1px solid #bfbfbf;
	margin-bottom: 20px;
	padding-bottom: 20px;
	font-weight: 600;
	font-size: 17px;
}

.carousel-control-next-icon, .carousel-control-prev-icon {
	width: 30px;
	height: 30px;
}
.carousel-control-next, .carousel-control-prev {
	background-color: rgba( 0, 0, 0, 0.25);
}

h7 {
	color: orange;
	text-shadow: 2px 2px 2px black;
	font-weight: bolder;
	font-size: 18px;
}

.link-green {
	display: inline-block;
	height: 40px;
	line-height: 40px;
	color: var(--main-text-color);
	background: var(--main-bg-color);
	text-transform: uppercase;
	border-radius: 30px;
	transition: all .3s ease-in-out;
}

.link-green:hover { background: #fff; color: var(--main-bg-color); box-shadow: 0 5px 15px rgba(0,0,0,.2); }

.text-big { color: #030303; font-size: 18px; text-transform: uppercase; margin-left: 15px; display: inline-block; }
.bg-blue .text-big { color: var(--main-text-color); }

.link-default {
	display: inline-block;
	height: 40px;
	line-height: 40px;
	color: var(--main-text-color);
	border: 1px solid var(--main-text-color);
	background: transparent;
	text-transform: uppercase;
	padding: 0 30px;
	border-radius: 30px;
	transition: all .3s ease-in-out;
}
	.link-default:hover { color: var(--main-bg-color); background: #fff; }

.link-small {
	display: inline-block;
	height: 30px;
	line-height: 30px;
	color: #196bb5;
	background: #fff;
	text-transform: uppercase;
	padding: 0 20px;
	border-radius: 30px;
	transition: all .3s ease-in-out;
	font-size: 11px;
	margin-left: 15px;
	margin-top: 13px;
}
	.link-small:hover { background: var(--main-bg-color); color: var(--main-text-color); }


/* HEADER */

header { position: absolute; top: 0px; left: 0px; right: 0px; width: 100%; z-index: 100; background-color: rgba(20, 52, 77, 0); }

.bg-green { padding: 20px 0; background: var(--main-bg-color); }
.bg-white { padding: 50px 0; background: #fff; }
.bg-gray { padding: 50px 0; background: #f6f6f6; }
.bg-blue {
	padding: 50px 0;
	/* Permalink - use to edit and share this gradient: http://colorzilla.com/gradient-editor/#184268+0,196bb5+100 */
	background: rgb(24,66,104); /* Old browsers */
	background: -moz-linear-gradient(top, rgba(24,66,104,1) 0%, rgba(25,107,181,1) 100%); /* FF3.6-15 */
	background: -webkit-linear-gradient(top, rgba(24,66,104,1) 0%,rgba(25,107,181,1) 100%); /* Chrome10-25,Safari5.1-6 */
	background: linear-gradient(to bottom, rgba(24,66,104,1) 0%,rgba(25,107,181,1) 100%); /* W3C, IE10+, FF16+, Chrome26+, Opera12+, Safari7+ */
	filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#184268', endColorstr='#196bb5',GradientType=0 ); /* IE6-9 */
}

.bg-blue ul li {
	color: var(--main-text-color);
	list-style-type: circle;
	margin-left: 20px;
}

.bg-blue blockquote {
	color: var(--main-text-color);
	border-left: 3px solid var(--main-text-color);
	padding-left: 0.5rem;
}


.box-linha {
	padding: 50px;
	padding-left: 210px;
	position: relative;
	padding-top: 35px;
	margin-bottom: 30px;
	transition: all .3s ease-in-out;
	border: 2px solid transparent;
	border-radius: 5px;
	max-height: 150px;
}


.box-linha.opacity { opacity: .4; }
.box-linha.active { opacity: 1; }


.box-linha img { position: absolute; top: 25px; left: 25px; }
.box-linha span { color: var(--main-text-color); font-size: 18px; text-transform: uppercase; font-weight: 600; }

.box-linha-holder:hover .box-linha { opacity: .4; }
.box-linha-holder .box-linha:hover { border: 2px solid var(--main-text-color); opacity: 1; box-shadow: 0 10px 25px rgba(0,0,0,.2); }

/* FOOTER */

.links { padding: 15px 0; background: #103353; border-top: 10px solid var(--main-text-color); }

footer { padding: 45px 0; background: #196bb5; }

.copyright { padding: 25px 0; background: var(--main-bg-color); }
.copyright p { color: var(--main-text-color); font-size: 12px; line-height: 20px; margin: 0; }
.copyright a { display: inline-block; margin-top: 10px; }

/* INTERNAS */

.title { height: 400px; padding-top: 200px; background: #194f7f; }
.title h1 { color: var(--main-text-color); text-shadow: 1px 1px #7d8693; font-size: 50px; font-weight: 400; text-transform: uppercase; line-height: 66px; width: 100%; }
.title h1 small { font-size: 30px; display: block; line-height: 34px; font-weight: 200; text-transform: none; }
#restrito-tecnicos{
    background-color: var(--main-bg-color);
}
#restrito-tecnicos .title {
	background-image: url('../Fig/brand_banner.jpg');
	background-position: center;
	background-repeat: no-repeat;
	background-size: cover;
}

.bg-highlight {
	padding: 60px 0 30px;
	position: relative;
	background: rgb(24,72,115); /* Old browsers */
	background: -moz-linear-gradient(top, rgba(24,72,115,1) 0%, rgba(25,107,181,1) 100%); /* FF3.6-15 */
	background: -webkit-linear-gradient(top, rgba(24,72,115,1) 0%,rgba(25,107,181,1) 100%); /* Chrome10-25,Safari5.1-6 */
	background: linear-gradient(to bottom, rgba(24,72,115,1) 0%,rgba(25,107,181,1) 100%); /* W3C, IE10+, FF16+, Chrome26+, Opera12+, Safari7+ */
	filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#184873', endColorstr='#196bb5',GradientType=0 ); /* IE6-9 */
}

.img-brand { position: absolute; top: 0; right: 0; bottom: 0; left: 200px; margin: auto; }

.link-social {
	width: 40px;
	height: 40px;
	display: inline-block;
	margin: 0 2px;
	background: #5991c3;
	color: var(--main-text-color);
	border-radius: 30px;
	text-align: center;
	font-size: 18px;
	line-height: 40px;
	transition: all .3s ease-in-out;
}
	.link-social:hover { opacity: .6; color: var(--main-text-color); }
	.facebook { background: #3b5998; }
	.linkedin { background: #0e76a8; }
	.whatsapp { background: #1bd741; }
	.e-mail { background: #3baadf; }

.link-medium {
	display: inline-block;
	height: 40px;
	line-height: 38px;
	border: 2px solid #5991c3;
	border-radius: 30px;
	color: #5991c3;
	text-align: center;
	padding: 0 30px;
	font-size: 16px;
	transition: all .3s ease-in-out;
	margin: 0 10px;
}
.link-medium:hover { background: #5991c3; color: var(--main-text-color); }

.box-gray { position: relative; }
.box-gray::before {
	content: '';
	background: #f5f5f5;
	position: absolute;
	top: 0;
	right: 15px;
	height: 100%;
	width: 4000px;
}
.box-gray * { position: relative; z-index: 10; }
.box-gray form { padding-right: 30px; margin-bottom: 40px; }

.map {
	margin-left: -30px;
    position: relative;
    padding-bottom: 100%;
    height: 0;
    overflow: hidden;
}
.map iframe {
    position: absolute;
    top: 0;
    left: 0;
    width: 100% !important;
    height: 100% !important;
}

input:disabled{
	color: white;
	background-color: rgba(239, 239, 239, 0.3);
}

textarea { height: 120px; padding: 15px; border: 1px solid #9e9e9e; }
select { margin-bottom: 15px; border: 1px solid #9e9e9e; }

.input-fake {
    width: 100%;
    margin-bottom: 15px;
    border: 2px solid #e2e2e2;
    height: 55px;
    line-height: 55px;
    border-radius: 10px;
    padding: 0 15px;
    position: absolute;
    top: 0;
    left: 0;
    transition: all .3s ease-in-out;
    text-align: center;
}

.input-fake i {
    margin-right: 10px;
}

input{
	font-family: inherit;
	font-size: inherit;
	border: none;
	border-radius: 6px;
	-moz-border-radius:6px;
	overflow: hidden;
}

footer form button { border-radius: 0; }

.highlight { font-size: 17px; }

.bg-blue p { color: var(--main-text-color); }


/* Bootstrap Toogle, for some fucking reason not included in bs */
/* https://cdn.jsdelivr.net/gh/gitbrent/bootstrap4-toggle@3.6.1/css/bootstrap4-toggle.css */
.btn-group-xs>.btn,.btn-xs{padding:.35rem .4rem .25rem .4rem;font-size:.875rem;line-height:.5;border-radius:.2rem}.checkbox label .toggle,.checkbox-inline .toggle{margin-left:-1.25rem;margin-right:.35rem}.toggle{position:relative;overflow:hidden}.toggle.btn.btn-light,.toggle.btn.btn-outline-light{border-color:rgba(0,0,0,.15)}.toggle input[type=checkbox]{display:none}.toggle-group{position:absolute;width:200%;top:0;bottom:0;left:0;transition:left .35s;-webkit-transition:left .35s;-moz-user-select:none;-webkit-user-select:none}.toggle-group label,.toggle-group span{cursor:pointer}.toggle.off .toggle-group{left:-100%}.toggle-on{position:absolute;top:0;bottom:0;left:0;right:50%;margin:0;border:0;border-radius:0}.toggle-off{position:absolute;top:0;bottom:0;left:50%;right:0;margin:0;border:0;border-radius:0;box-shadow:none}.toggle-handle{position:relative;margin:0 auto;padding-top:0;padding-bottom:0;height:100%;width:0;border-width:0 1px;background-color:#fff}.toggle.btn-outline-primary .toggle-handle{background-color:var(--primary);border-color:var(--primary)}.toggle.btn-outline-secondary .toggle-handle{background-color:var(--secondary);border-color:var(--secondary)}.toggle.btn-outline-success .toggle-handle{background-color:var(--success);border-color:var(--success)}.toggle.btn-outline-danger .toggle-handle{background-color:var(--danger);border-color:var(--danger)}.toggle.btn-outline-warning .toggle-handle{background-color:var(--warning);border-color:var(--warning)}.toggle.btn-outline-info .toggle-handle{background-color:var(--info);border-color:var(--info)}.toggle.btn-outline-light .toggle-handle{background-color:var(--light);border-color:var(--light)}.toggle.btn-outline-dark .toggle-handle{background-color:var(--dark);border-color:var(--dark)}.toggle[class*=btn-outline]:hover .toggle-handle{background-color:var(--light);opacity:.5}.toggle.btn{min-width:3.7rem;min-height:2.15rem}.toggle-on.btn{padding-right:1.5rem}.toggle-off.btn{padding-left:1.5rem}.toggle.btn-lg{min-width:5rem;min-height:2.815rem}.toggle-on.btn-lg{padding-right:2rem}.toggle-off.btn-lg{padding-left:2rem}.toggle-handle.btn-lg{width:2.5rem}.toggle.btn-sm{min-width:3.125rem;min-height:1.938rem}.toggle-on.btn-sm{padding-right:1rem}.toggle-off.btn-sm{padding-left:1rem}.toggle.btn-xs{min-width:2.19rem;min-height:1.375rem}.toggle-on.btn-xs{padding-right:.8rem}.toggle-off.btn-xs{padding-left:.8rem}
)=====";
#pragma endregion // Brand 
