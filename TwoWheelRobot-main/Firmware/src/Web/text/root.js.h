#pragma once

#include <pgmspace.h>

#pragma region NavitasRoot
const char NAVITAS_ROOT_JS[] PROGMEM = R"=====(
var _staticSVG_HTML = null;
var selected = null;

function fncNetworkSelected(){
	var selectGroup = document.getElementById('wifiNetworks');
	if( selectGroup.selectedIndex > -1 ) {
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

function fncGetRadioQuality( _rssi ) {
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

function fncHandleRedeXML( _XMLHttpRequest ) {
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

function fncBtnRefresh_Enable() {
	var btnRefresh = document.getElementById('btnRefresh');
	btnRefresh.disabled = 0;
	btnRefresh.classList.remove('btnDisabled');
	document.getElementById('btnRefreshSVG').innerHTML = _staticSVG_HTML;
}

function fncBtnRefresh_Click() {
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
)=====";
#pragma endregion // NavitasRoot
