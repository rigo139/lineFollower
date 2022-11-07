var hasInternet = window.location.hostname.indexOf('192.168.4.1') == -1;
var _ = document.createElement('script');
_.setAttribute('src', hasInternet ? 'https://code.jquery.com/jquery-2.2.4.js' : '/Resources/JS/jquery.js' );
_.setAttribute('type', 'text/javascript' );
document.head.appendChild( _ );
//-------------------------

var _includeList = null;
var _includeErrorList = [];
var _includedElements = 0;
function loadIncludes( includeList ){
	_includeList = includeList;
	if (!window.jQuery) { setTimeout(function() { loadIncludes( _includeList ) }, 50 ); return; }
	_includedElements = 0;
	for( var j=0; j<_includeList.length; j++ ){ _includeList[j] = [0].concat(_includeList[j]); }
	loadInclude( _includeList[0] );
}

function loadInclude( item ){
	var includeObj = null;
	if( item[1] == 'text/javascript' ){
		includeObj = document.createElement('script');
		loadWithSrc( includeObj, item );
	}else if(item[1] == 'text/css'){
		includeObj = document.createElement('link');
		loadCSS( includeObj, item );
	}else{
		includeObj = document.createElement('img');
		loadWithSrc( includeObj, item );
		includeObj.setAttribute('style', 'display:none;');
	}
	if( hasInternet && item[4] ){
		includeObj.integrity = item[4];
		includeObj.crossOrigin = 'anonymous';
	}
	includeObj.setAttribute('type', item[1] );
	includeObj.addEventListener( 'load', onIncludeLoad );
	includeObj.addEventListener( 'error', onIncludeError );
	document.head.appendChild(includeObj);
}

function loadCSS( includeObj, obj ){
	includeObj.rel  = 'stylesheet';
	let reloadFix = ( ((obj[0]>0) && (includeObj.outerHTML.indexOf('img')==-1)) ? '?v=' + obj[0] : '');
	if( hasInternet && obj[3] ){
		includeObj.href = obj[3] + reloadFix;
	}else{
		includeObj.href = obj[2] + reloadFix;
	}
}

function loadWithSrc( includeObj, obj ){
	let reloadFix = ( ((obj[0]>0) && (includeObj.outerHTML.indexOf('img')==-1)) ? '?v=' + obj[0] : '');
	if( hasInternet && obj[3] ){
		includeObj.src = obj[3] + reloadFix;
	}else{
		includeObj.src = obj[2] + reloadFix;
	}
}

function onIncludeError( event ){
	_includeErrorList.push( event );
	var i = getIndexFromIncludeError( event );
	document.head.removeChild( event.srcElement );
	if( i != null ){
		_includeList[i][0]++;
		if( _includeList[i][0] > 3 ){
			setTimeout(() => { loadInclude( _includeList[i] ); }, 1000 );
		}else{
			loadInclude( _includeList[i] );
		}
	}
}

function onIncludeLoad( event ){
	_includedElements++;
	if(  _includedElements < _includeList.length ){
		loadInclude( _includeList[_includedElements] );
	}else{
		const css = "@font-face { font-family: 'Nunito'; font-style: italic; font-weight: 200; src: local('Nunito ExtraLight Italic'), local('Nunito-ExtraLightItalic'), url('./Resources/nunito_italic_200.woff2') format('woff2'); unicode-range: U+0000-00FF, U+0131, U+0152-0153, U+02BB-02BC, U+02C6, U+02DA, U+02DC, U+2000-206F, U+2074, U+20AC, U+2122, U+2191, U+2193, U+2212, U+2215, U+FEFF, U+FFFD; }";
		const head = document.getElementsByTagName('head')[0];
		const style = document.createElement('style');
		style.appendChild(document.createTextNode(css));
		head.appendChild(style);
	}
}

function getIndexFromIncludeError( event ){
	var temp = event.target.outerHTML;
	var path = temp.substring( temp.indexOf('src=') + 5 );
	path = path.substring(0, path.indexOf("\"") );
	for(let i=0; i<_includeList.length; i++){
		if( (path.indexOf(_includeList[i][2] != -1)) || (path._includeList[i][3] != -1) ){
			return i;
		}
	}
	return null;
}

function _loadPage(){
	if( (_includeList == null) || _includedElements != _includeList.length ){
		setTimeout(() => { _loadPage(); }, 10 );
		return;	
	}
	var obj = document.getElementById('pgTitle');
	obj.innerHTML = pgTitleHTML;
	document.title = obj.innerText;
	obj.innerHTML += pgSubtitleHTML;
	document.getElementById('bodyHTML').innerHTML = bodyHTML;
	setTimeout(() => { fncOnLoaded(); }, 10 );
}

function fncScrollInto( _id ){
	document.getElementById( _id ).scrollIntoView({behavior: 'smooth', block: 'start', inline: 'nearest'});
}

function fncDisableByID( _id ){
	var btnObj = document.getElementById( _id );
	btnObj.disabled = 1;
	btnObj.classList.add('btnDisabled');
}

function fncEnableByID( _id ){
	var btnObj = document.getElementById( _id );
	btnObj.disabled = 0;
	btnObj.classList.remove('btnDisabled');
}

function fncGetXML(_path, _handler) {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			_handler( this );
		}
	};
	xhttp.open('GET', _path, true);
	xhttp.send();
}

function fncGetJSON(_path, _handler) {
	var rawFile = new XMLHttpRequest();
	rawFile.overrideMimeType("application/json");
	rawFile.open("GET", _path, true);
	rawFile.onreadystatechange = function() {
		if (rawFile.readyState === 4 && rawFile.status == "200") {
			var temp = rawFile.responseText;
			try{
				_handler( JSON.parse(temp) );
			}catch(err){
				console.log( err.message );
				console.log( temp );
			}
		}
	}
	rawFile.send(null);
}

function zeroPad(nr,base){
	var  len = (String(base).length - String(nr).length)+1;
	return len > 0? new Array(len).join('0')+nr : nr;
}

function fadeInDFlex(id){
	$('#' + id).removeClass('d-none');
    $('#' + id).addClass('d-flex');
}

function fadeOutDFlex(id){
	$('#' + id).removeClass('d-flex');
	$('#' + id).addClass('d-none');
}
function fncDefaultToggle( obj, onShowCallback ){
	let _id = '#' + obj.nextElementSibling.id;
	if( $( _id ).is( ":hidden" ) ){
        $('#navOptions .collapse').collapse('hide');
		$( _id ).collapse('show');
		setTimeout(() => { fncScrollInto( _id.substr(1) ); }, 200);
		if( typeof(onShowCallback) == 'function' ){ onShowCallback(); }
    }else{
        $(_id).collapse('hide');
    }
}