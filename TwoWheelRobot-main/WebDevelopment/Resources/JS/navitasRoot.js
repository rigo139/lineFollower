// ---------------------------
// WiFi List table functions
var _staticSVG_HTML = null;
var selected = null;

function fncNetworkSelected(){
	var selectGroup = document.getElementById('wifiNetworks');
	if( selectGroup.selectedIndex > -1 )
	{
		document.getElementById('SSID').value = selectGroup.options[ selectGroup.selectedIndex ].value;
		document.getElementById('PSWD').value = '';
	}
}

function fncFillFields(){
	document.getElementById('SSID').value = selected.children[0].innerText;
	var _pswd = document.getElementById('PSWD');
	_pswd.disabled = 0;
	if( !fncIsLocked() ){
		_pswd.value = '';
		_pswd.disabled = 1;
	}
	_pswd.required = !_pswd.disabled;
}

function fncIsLocked(){
	if( selected ){
		return (selected.children[1].innerHTML.indexOf('Unlocked') < 0);
	}
	return 0;
}

function fncGetNetworks() {
	fncGetXML( 'rede.xml', fncHandleRedeXML );
}

function fncGetRadioQuality( _rssi )
{
	if(      _rssi > -50 ){ return 4; } 
	else if( _rssi > -70 ){ return 3; } 
	else if( _rssi > -90 ){ return 2; } 
	return 1;
}

function addRow( _SSID, _RSSI, _LOCKED) {
	if (!document.getElementsByTagName) { return; }

	var tab     = document.getElementById('tableEntries');
	var tabBody = tab.tBodies.item(0);
	var row     = document.createElement('tr');
	row.id      = tab.rows.length;
	row.classList.add('d-flex');

	var cell1     = document.createElement('td');
	cell1.classList.add('col-9');
	var textnode1 = document.createTextNode(_SSID);
	cell1.appendChild(textnode1);
	row.appendChild(cell1);

	cell2     = document.createElement('td');
	cell2.classList.add('col-3');
	var tempHTML = '<svg class="wifiStrengthSVG"> <use xlink:href="#';
	if( _LOCKED ){
		tempHTML += 'wifiLocked_';
	}else{
		tempHTML += 'wifiUnlocked_';
	}
	tempHTML    += _RSSI + '"/> </svg>';
	cell2.innerHTML = tempHTML;
	row.appendChild(cell2);

	tabBody.appendChild(row);
	tableHighlightRow();
}

function fncClearTable(){
	if (!document.getElementsByTagName) { return; }
	var tab     = document.getElementById('tableEntries');
	var tabBody = tab.tBodies.item(0);
	tabBody.innerHTML = '';
}

function fncHandleRedeXML( _XMLHttpRequest )
{
	var wifiList = _XMLHttpRequest.responseXML.getElementsByTagName('wifi');

	fncClearTable();
	for(var i=0; i<wifiList.length; i++)
	{
		var _ssid = '';
		var _rssi = 0;
		var _encr = 0;

		_ssid = wifiList[i].getElementsByTagName('ssid')[0].innerHTML;
		_rssi = fncGetRadioQuality( wifiList[i].getElementsByTagName('rssi')[0].innerHTML );
		_encr = +wifiList[i].getElementsByTagName('encr')[0].innerHTML;

		addRow( _ssid , _rssi, _encr);
	}
	fncBtnRefresh_Enable();
}

function fncBtnRefresh_Enable(){
	var btnRefresh = document.getElementById('btnRefresh');
	btnRefresh.disabled = 0;
	btnRefresh.classList.remove('btnDisabled');
	document.getElementById('btnRefreshSVG').innerHTML = _staticSVG_HTML;
}

function fncBtnRefresh_Click(){
	var btnRefresh = document.getElementById('btnRefresh');
	if( !btnRefresh.disabled )
	{
		btnRefresh.disabled = 1;
		btnRefresh.classList.add('btnDisabled');

		var _staticSVG   = document.getElementById('btnRefreshSVG');
		var _animatedSVG = document.getElementById('refreshSVG');
		_staticSVG_HTML = _staticSVG.innerHTML;
		_staticSVG.innerHTML = _animatedSVG.innerHTML;
		setTimeout( fncBtnRefresh_Enable , 10000 );
		fncGetNetworks();
	}
}

function tableHighlightRow() {
	if (document.getElementById && document.createTextNode) {
		var tables = document.getElementsByTagName('table');
		for (var i = 0; i < tables.length; i++) {
			if (tables[i].id == 'tableEntries') {
				var trs = tables[i].getElementsByTagName('tr');
				for (var j = 0; j < trs.length; j++) {
					if (trs[j].parentNode.nodeName === 'TBODY') {
						trs[j].onmouseover = function () {
							if ( !this.classList.contains('highlight') ) {
								this.classList.add( 'highlight' );
							}
							return false
						}
						trs[j].onmouseout = function () {
							if (this.classList.contains('highlight') ) {
								this.classList.remove('highlight');
							}
							return false
						}
						trs[j].onmousedown = function () {

							if ( !this.classList.contains('clicked') ){
								if (selected !== null) {
									selected.classList.remove('clicked');
								}

								this.classList.add('clicked');
								selected = this;
								fncFillFields();
							}
							else {
								this.classList.remove('clicked');
								selected = null;
								document.getElementById('SSID').value = '';
								var _pswd = document.getElementById('PSWD');
								_pswd.value = '';
								_pswd.disabled = 0;
								_pswd.required = 0;
							}

							return true
						}
					}
				}
			}
		}
	}
}

// Firmware
function fncGetFirmwareInfo(){
	fncGetJSON( 'firmware.json' , fncHandleFirmwareJson );
}

var _jsonFirmware = null;
function fncHandleFirmwareJson( file ){
	if( !file ){return;}
	_jsonFirmware = file;

	$('#vIDF').val( file.hasOwnProperty('IDF') ? file['IDF'] : '' );
	$('#vFirmVersion').val( file.hasOwnProperty('Version') ? file['Version'] : '' );
	$('#vFirmDate').val( file.hasOwnProperty('Date') ? file['Date'] : '' );
}

function fncStartUploading(obj){
	fadeOutDFlex('trStartUpload');
	fadeInDFlex('trBinFile');
	$('#binFile').click();
}

var binFile = null;
var binMD5 = null;
function fncBinLoaded(obj){
	binFile = obj.files[0];

	let reader = new FileReader();
	reader.onload = function(e){

		binMD5 = md5(e.target.result);

		$('#vFileName').val( binFile.name );
		fadeInDFlex('trMD5Auto');
		fadeInDFlex('trMD5');
		$('#vMD5Auto').val( binMD5 );
		$('#md5File').click();
		fncOnInputChangeMD5();
	}
	reader.readAsArrayBuffer( binFile );
}

function fncMD5Loaded(obj){
	md5File = obj.files[0];

	let reader = new FileReader();
	reader.onload = function(e){
		$('#vFirmMD5').val( e.target.result.toLowerCase() );
		fncOnInputChangeMD5();
	}
	reader.readAsText( md5File );
}

function fncOnInputChangeMD5(obj){
	if( $('#vMD5Auto').val().toLowerCase() == $('#vFirmMD5').val().toLowerCase() ){
		fadeInDFlex('trUploadBin');
	}else{
		fadeOutDFlex('trUploadBin');
	}
}

function fncUploadBin(obj){
	let confirmResult = confirm('A atualização pode levar vários minutos!\r\nTem certeza que deseja continuar?');
	if( confirmResult ){
		$('#vFirmMD5').prop("disabled", false);
		fadeOutDFlex('trBinFile');
		fadeOutDFlex('trMD5Auto');            
		fadeOutDFlex('trMD5');
		fadeOutDFlex('trUploadBin');
		fadeInDFlex('trProgressBar');

		$('#formFirmware').submit( fncOnUploadSubmit );
		$('#btnSubmitFirmware').click();
	}
}

function fncSetUploadProgress(value){
		$('#uploadProgressBar').css('width', value+'%').attr('aria-valuenow', value);
		$('#uploadProgressBarText').html(value + '%');
	}

function fncOnUploadSubmit(e){
	e.preventDefault();
	var form = $('#formFirmware')[0];
	var data = new FormData(form);
	$.ajax({
		url: form.action,
		type: form.method,
		data: data,
		contentType: false,
		processData: false,
		xhr: fncGetFormUploadAjax,
		success: function(d, s) { console.log('Sucesso!') },
		error: function (a, b, c) { console.log(a, b, c); }
	});
}

function fncGetFormUploadAjax(){
	var xhr = new window.XMLHttpRequest();
	xhr.onreadystatechange = function () {
		if (xhr.status) {
			console.log( xhr.status );
		}
	}
	xhr.upload.addEventListener('progress', function(evt) {
		if (evt.lengthComputable) {
			const per = 100 * ( evt.loaded / evt.total );
			console.log( per, evt.loaded, evt.total );
			fncSetUploadProgress( per );
		}
	}, false);
	xhr.upload.addEventListener('loadend', function(evt){
		console.log("Upload Ended");
		setTimeout( () => { location.reload(); }, 5000 );
	})
	return xhr;
}