#pragma once

#pragma region XML
const char XML_START[] = R"=====(<?xml version='1.0'?>
<response>
)=====";

const char XML_END[] = R"=====(</response>)=====";
#pragma endregion // AP_ROOT_XML

#pragma region HTML_ROOT

const char REDIRECT_TO_ROOT[] PROGMEM = R"=====(
<html><script>window.location.href="/"</script></html>
)=====";

const char HTML_ROOT[] PROGMEM = R"=====(
<!DOCTYPE html>
<html class="js" lang="pt-BR">
<head>
    <script src="/Resources/JS/navitas.js" onerror='window.stop(); setTimeout( () => { location.reload(); }, 1000 );'></script>
	<meta charset="utf-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <meta name="author" content="Wellington R Gallo (wellington@navitastecnologia.com.br)">
    
	<title>Two Wheel Robot</title>
    <link rel="icon" href="/Resources/Fig/favicon.png">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
    
    <script>        
        loadIncludes( [ 
                         ['image/png'      , '/Resources/Fig/logo.png'        ]
                        ,['image/jpeg'     , '/Resources/Fig/brand_banner.jpg']
                        ,['image/png'      , '/Resources/Fig/navitas.png'     ]
                        ,['text/css'       , '/Resources/CSS/bootstrap.css'   , 'https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/css/bootstrap.min.css']
                        ,['text/javascript', '/Resources/JS/bootstrap.js'     , 'https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/js/bootstrap.min.js']
                        ,['text/css'       , '/Resources/CSS/brand.css'       ]
                        ,['text/javascript', '/Resources/JS/md5.min.js'       ]
                        ,['text/javascript', '/Resources/JS/navitasRoot.js'   ]
                    ]);
    </script>

<style>
    #btnRefresh svg {
        fill: darkorange;
        width: 24px;
        height: 24px;
    }

    .wifiStrengthSVG{
        fill: darkorange;
        width:  32px;
        height: 32px;
        text-align: center;
        justify-content: center;
        align-items: center;
    }

    #tableEntries tr.clicked {
        background: darkgray;
    }

    #tableEntries tr.highlight {
        background: gray;
    }

    .table-fixed{
        overflow-y: hidden;
    }

    .table-fixed tbody {
        height: 200px;
        overflow-y: auto;
        width: 100%;
    }

    .table-fixed thead,
    .table-fixed tbody,
    .table-fixed tr,
    .table-fixed td,
    .table-fixed th { display: block; }

    .table-fixed tbody td,
    .table-fixed tbody th,
    .table-fixed thead > tr > th {
        float: left;
        position: relative;
    }

</style>

<svg style='display: none;'>
    <symbol id='wifiUnlocked'><svg viewBox='0 0 18 18' preserveAspectRatio='none'><path fill-opacity='.7' d='M9.01 15.99l8.8-10.96C17.47 4.77 14.08 2 9 2S.53 4.77.19 5.03l8.8 10.96h.02z'/></svg></symbol>

    <symbol id='wifiRefresh'><svg xmlns='http://www.w3.org/2000/svg' width='24' height='24' viewBox='0 0 24 24' ><path d='M5 18c4.667 4.667 12 1.833 12-4.042h-3l5-6 5 6h-3c-1.125 7.98-11.594 11.104-16 4.042zm14-11.984c-4.667-4.667-12-1.834-12 4.041h3l-5 6-5-6h3c1.125-7.979 11.594-11.104 16-4.041z'/></svg></symbol>

    <symbol id='wifiRefreshing'>
        <svg id='refreshSVG' xmlns='http://www.w3.org/2000/svg' xmlns:svg='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' width='24' height='24' viewBox='0 0 24 24' >
                <path d='M5 18c4.667 4.667 12 1.833 12-4.042h-3l5-6 5 6h-3c-1.125 7.98-11.594 11.104-16 4.042zm14-11.984c-4.667-4.667-12-1.834-12 4.041h3l-5 6-5-6h3c1.125-7.979 11.594-11.104 16-4.041z'/>            
            <animateTransform 
                attributeName='transform'
                attributeType='XML'
                type='rotate'
                dur='1s'
                from='180'
                to='0'
                repeatCount='indefinite'
            />
        </svg>
    </symbol>

    <symbol id='wifiUnlocked_1'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path fill-opacity='.3' d='M24.02 42.98L47.28 14c-.9-.68-9.85-8-23.28-8S1.62 13.32.72 14l23.26 28.98.02.02.02-.02z'/><path d='M13.34 29.72l10.65 13.27.01.01.01-.01 10.65-13.27C34.13 29.31 30.06 26 24 26s-10.13 3.31-10.66 3.72z'/></svg></symbol>
    <symbol id='wifiUnlocked_2'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path fill-opacity='.3' d='M24.02 42.98L47.28 14c-.9-.68-9.85-8-23.28-8S1.62 13.32.72 14l23.26 28.98.02.02.02-.02z'/><path d='M9.58 25.03l14.41 17.95.01.02.01-.02 14.41-17.95C37.7 24.47 32.2 20 24 20s-13.7 4.47-14.42 5.03z'/></svg></symbol>
    <symbol id='wifiUnlocked_3'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path fill-opacity='.3' d='M24.02 42.98L47.28 14c-.9-.68-9.85-8-23.28-8S1.62 13.32.72 14l23.26 28.98.02.02.02-.02z'/><path d='M7.07 21.91l16.92 21.07.01.02.02-.02 16.92-21.07C40.08 21.25 33.62 16 24 16c-9.63 0-16.08 5.25-16.93 5.91z'/></svg></symbol>
    <symbol id='wifiUnlocked_4'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path d='M24.02 42.98L47.28 14c-.9-.68-9.85-8-23.28-8S1.62 13.32.72 14l23.26 28.98.02.02.02-.02z'/></svg></symbol>
    <symbol id='wifiLocked_1'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path d='M41 19c.7 0 1.4.1 2.1.2l4.2-5.2c-.9-.7-9.8-8-23.3-8S1.6 13.3.7 14L24 43l7-8.7V29c0-5.5 4.5-10 10-10z' opacity='.3'/><path d='M46 32v-3c0-2.8-2.2-5-5-5s-5 2.2-5 5v3c-1.1 0-2 .9-2 2v8c0 1.1.9 2 2 2h10c1.1 0 2-.9 2-2v-8c0-1.1-.9-2-2-2zm-2 0h-6v-3c0-1.7 1.3-3 3-3s3 1.3 3 3v3zm-30.7-2.3l9 11.2L24 43l7-8.8V29c0-.5 0-1 .1-1.4-1.8-.8-4.2-1.6-7.1-1.6-6.1 0-10.1 3.3-10.7 3.7z'/></svg></symbol>
    <symbol id='wifiLocked_2'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path opacity='.3' d='M41 19c.7 0 1.4.1 2.1.2l4.2-5.2c-.9-.7-9.9-8-23.3-8S1.6 13.3.7 14L24 43l7-8.7V29c0-5.5 4.5-10 10-10z'/><path d='M46 32v-3c0-2.8-2.2-5-5-5s-5 2.2-5 5v3c-1.1 0-2 .9-2 2v8c0 1.1.9 2 2 2h10c1.1 0 2-.9 2-2v-8c0-1.1-.9-2-2-2zm-2 0h-6v-3c0-1.7 1.3-3 3-3s3 1.3 3 3v3zM9.6 25L24 43l7-8.7V29c0-2.6 1-5 2.7-6.8C31.2 21 27.9 20 24 20c-8.2 0-13.7 4.5-14.4 5z'/></svg></symbol>
    <symbol id='wifiLocked_3'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path opacity='.3' enable-background='new' d='M41 19c.7 0 1.4.1 2.1.2l4.2-5.2c-.9-.7-9.8-8-23.3-8S1.6 13.3.7 14L24 43l7-8.7V29c0-5.5 4.5-10 10-10z'/><path d='M46 32v-3c0-2.8-2.2-5-5-5s-5 2.2-5 5v3c-1.1 0-2 .9-2 2v8c0 1.1.9 2 2 2h10c1.1 0 2-.9 2-2v-8c0-1.1-.9-2-2-2zm-2 0h-6v-3c0-1.7 1.3-3 3-3s3 1.3 3 3v3zM7.1 21.9L24 43l7-8.7V29c0-4.3 2.7-8 6.5-9.4C34.6 18 29.9 16 24 16c-9.6 0-16.1 5.2-16.9 5.9z'/></svg></symbol>
    <symbol id='wifiLocked_4'><svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 48 48'><path d='M41 19c.72 0 1.41.08 2.09.22L47.28 14c-.9-.68-9.85-8-23.28-8S1.62 13.32.72 14l23.26 28.98.02.02.02-.02 6.98-8.7V29c0-5.52 4.48-10 10-10zm5 13v-3c0-2.76-2.24-5-5-5s-5 2.24-5 5v3c-1.1 0-2 .9-2 2v8c0 1.1.9 2 2 2h10c1.1 0 2-.9 2-2v-8c0-1.1-.9-2-2-2zm-2 0h-6v-3c0-1.66 1.34-3 3-3s3 1.34 3 3v3z'/></svg></symbol>

</svg>

<script>
    var pgTitleHTML = 'Protótipo';
    var pgSubtitleHTML = '<small>Seguidor de Linha RC</small>';
    
    var bodyHTML =	`
<div style='text-align: center; background-color: black;  padding-top: 10px; padding-bottom: 10px;'>
    <div id='navOptions'>

    <!-- Status -->
    <div class="container-fluid" style='padding-bottom: 5px'>
        <nav class="navbar navbar-expand-lg navbar-light bg-dark" onclick='fncToggleStatus()'>
            <h4 >Status</h4>
        </nav>
        <div id="collapseStatus" class="collapse">
            <br/>
            <div class='row'>
                <div class='col-12 col-md-6 mx-auto'>
                    <table class='table table-dark text-center' id='tableStatus'><tbody></tbody></table>
                </div>
            </div>
        </div>
    </div>
    
    <!-- Controle -->
    <div class="container-fluid" style='padding-bottom: 5px'>
        <nav class="navbar navbar-expand-lg navbar-light bg-dark" onclick='fncToggleControl()'>
            <h4 >Controle</h4>
        </nav>
        <div id="collapseControl" class="collapse">
            <br/>

            <div class='row'>
                <div class='col-12'>
                    <p id='lblWebSocketsStatus'>Erro</p>
                </div>
            </div>
            <br/>
            <br/>

            <!-- Switches -->   
            <div class='row'>
                <div class='col-4'><p>Direção</p></div>
                <div class='col-4'><p>Energia</p></div>
                <div class='col-4'><p>Velocidade</p></div>
            </div>
            <div class='row'>
                <div class='col-4'><input id='chkAutoSteering' data-width='90%' type='checkbox' data-on="Auto" data-off="Manual" data-offstyle='secondary' checked data-toggle='toggle' onChange='fncOnSwitchesChange()'></div>
                <div class='col-4'><input id='chkPower' data-width='90%' type='checkbox' data-onstyle='success' data-offstyle='danger' data-toggle='toggle' onChange='fncOnSwitchesChange()'></div>
                <div class='col-4'><input id='chkAutoThrottle' data-width='90%' type='checkbox' data-on='Auto' data-off='Manual' data-offstyle='secondary' checked data-toggle='toggle' onChange='fncOnSwitchesChange()'></div>
            </div>
            <br/>
        
            
            <!-- Controle de Velocidade -->
            <div class='row'>
                <div class='col-8 mx-auto'>
                    <label for="rangeSpeed">Velocidade</label>
                    <input disabled id="rangeSpeed" style='height: 20px;' type="range" class="custom-range" min="0" max="255" step="1">
                </div>
            </div>
            <br/>

            <!-- Controle de Direcao -->
            <div class='row'>
                <div class='col-8 mx-auto'>
                    <label for="rangeSteering">Direção</label>
                    <input disabled id="rangeSteering" style='height: 20px;' type="range" class="custom-range" min="-127" max="127" step="1">
                </div>
            </div>
            <br/>
            
            <!-- QTR Info -->
            <div class='row'>
                <div class='col-11 mx-auto'>
                    <div class='row'>
                        <input id='numQtr0' class='text-center col qtrText' type='text' value='QTR 1' disabled>
                        <input id='numQtr1' class='text-center col qtrText' type='text' value='QTR 2' disabled>
                        <input id='numQtr2' class='text-center col qtrText' type='text' value='QTR 3' disabled>
                        <input id='numQtr3' class='text-center col qtrText' type='text' value='QTR 4' disabled>
                        <input id='numQtr4' class='text-center col qtrText' type='text' value='QTR 5' disabled>
                        <input id='numQtr5' class='text-center col qtrText' type='text' value='QTR 6' disabled>
                        <input id='numQtr6' class='text-center col qtrText' type='text' value='QTR 7' disabled>
                        <input id='numQtr7' class='text-center col qtrText' type='text' value='QTR 8' disabled>
                    </div>
                </div>
            </div>
            <br/>

            <!-- QTR Calibration -->
            <div class='row'>
                <div class='col'><label for="numQtrMin">QTR Mín</label></div>
                <div class='col'><label for="numSteeringGain">Sensibilidade</label></div>
                <div class='col'><label for="numQtrMax">QTR Máx</label></div>
            </div>
            <div class='row'>
                <div class='col'><input type="number" id="numQtrMin" class='col-10 text-center quantity' min="0" max="4095" value='800'></div>
                <div class='col'><input type="number" id="numSteeringGain" class='col-10 text-center quantity' min="0.1" max="2.0" value='1.0' step='0.1'></div>
                <div class='col'><input type="number" id="numQtrMax" class='col-10 text-center quantity' min="0" max="4095" value='1600'></div>
            </div>
            <br/>

        </div>
    </div>
    
    <!-- Wi-Fi -->
    <div class="container-fluid" style='padding-bottom: 5px'>
        <nav class="navbar navbar-expand-lg navbar-light bg-dark" onclick='fncToggleNetwork()' >
            <h4 >Wi-Fi</h4>
        </nav>
        <div id="collapseSetupRede" class="collapse">
            <br/>
    
            <div class='col-12 col-md-8 col-lg-6 mx-auto'>
                <h4>Selecione a rede 802.11 b/g/n</h4>
                
                <form id='formRede' action='/connectToWifi'>
                    <div class=' divTableEntries table-dark' id='idDivTableEntries'>
                        <table class='container-fluid table-fixed' id='tableEntries' cellspacing='0' cellpadding='1'>
                            <thead class='table-dark'>
                                <tr class='d-flex'>
                                    <th class='col-9'>SSID</th>
                                    <th class='col-3'>RSSI</th>
                                </tr>
                            </thead>
                            <tbody></tbody>
                        </table>
                    </div>
                        
                    <br/>
                    <div class='container-fluid' style='padding-bottom: 5px;'>
                        <input maxlength='32' class='col-12 textCentered' type='text' id='SSID' name='SSID' placeholder='SSID' required>
                    </div>
                    <div class='container-fluid' style='padding-bottom: 5px;'>
                        <input minlength='8' maxlength='32' class='col-12 textCentered' type='password' id='PSWD' name='PSWD' placeholder='Password' autocomplete='one-time-code'>
                    </div>
                
                    <br/>
                    <div class='container-fluid' style='background-color: inherit; margin-bottom: 10px;'>
                        <div class='row'>
                            <div class='col-6'>
                                <a type='button' id='btnRefresh' class='centered btnForm link-green' onclick='fncBtnRefresh_Click()'><svg id='btnRefreshSVG'><use xlink:href='#wifiRefreshing' /></svg> &nbsp;Atualizar</a>
                            </div>
                            <div class='col-6'>
                                <a type='button' class='btnForm link-green' onclick='fncApplyNetwork()'>Aplicar</a> 
                                <input type='submit' id='btnSubmitWiFi' hidden>
                            </div>
                        </div>
                    </div>
                </form> 
            </div>
        </div>
    </div>
    
    <!-- Firmware -->
    <div class="container-fluid" style='padding-bottom: 5px'>
        <nav class="navbar navbar-expand-lg navbar-light bg-dark" onclick='fncToggleFirmware()' >
            <h4 >Firmware</h4>
        </nav>
        <div id="collapseFirmware" class="collapse">
            <br/>
    
            <div class='col-12 col-md-8 col-lg-6 mx-auto'>
                
                <form id='formFirmware' action='/uploadFirmware' method='POST' enctype='multipart/form-data'>
                    <input type='submit' id='btnSubmitFirmware' hidden>
                    <table class='table table-dark text-center'>
    
                        <tr class='d-flex'>
                            <td class='col-4'>ESP-IDF</td>
                            <td class='col-8'>
                                <input class='text-center col-12' type="text" id="vIDF" disabled>
                            </td>
                        </tr>
    
                        <tr class='d-flex'>
                            <td class='col-4'>Versão Atual</td>
                            <td class='col-8'>
                                <input class='text-center col-12' type="text" id="vFirmVersion" disabled>
                            </td>
                        </tr>
    
                        <tr class='d-flex'>
                            <td class='col-4'>Data Compilação</td>
                            <td class='col-8'>
                                <input class='text-center col-12' type="text" id="vFirmDate" disabled>
                            </td>
                        </tr>
    
                        <tr id='trProgressBar' class='d-none'>
                            <td class='col-12'>
                                <div class="progress">
                                    <div id='uploadProgressBar' class="progress-bar progress-bar-striped progress-bar-animated" role="progressbar" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100" style="width: 0%">
                                        <div id='uploadProgressBarText'></div>
                                    </div>
                                </div>
                            </td>
                        </tr>
    
                        <tr id='trStartUpload' class='d-flex'>
                            <td class='col-12'>
                                <div class='col-8 col-sm-6 mx-auto'>
                                    <a type='button' id='btnStartUploading' class='centered btnForm link-green' onclick='fncStartUploading(this)'>Atualizar</a>
                                </div>
                            </td>
                        </tr>
    
                        <tr id='trBinFile' class='d-none'>
                            <td class='col-4'>
                                <input type='file' id='binFile' name='FILE' accept=".bin" onchange='fncBinLoaded(this)' required hidden>
                                <input type="button" class="form-control-file" value="Arquivo Firmware" onclick="$('#binFile').click();" />
                            </td>
                            <td class='col-8'>
                                <input class='text-center col-12' type="text" id="vFileName" disabled>
                            </td>
                        </tr>
    
                        <tr id='trMD5Auto' class='d-none'>
                            <td class='col-4'>MD5 Calculado</td>
                            <td class='col-8'>
                                <input class='text-center col-12' type="text" id="vMD5Auto" maxlength='34' disabled>
                            </td>
                        </tr>
    
                        <tr id='trMD5' class='d-none'>
                            <td class='col-4'>
                                <input type='file' id='md5File' accept='.md5' onchange='fncMD5Loaded(this)' hidden>
                                <input type="button" class="form-control-file" value="Arquivo MD5" onclick="$('#md5File').click();" />
                            </td>
                            <td class='col-8'>
                                <input class='text-center col-12' placeholder='MD5' type="text" id="vFirmMD5" name="MD5" maxlength='34' disabled required>
                            </td>
                        </tr>
    
                        <tr id='trUploadBin' class='d-none'>
                            <td class='col-12'>
                                <div class='col-8 col-sm-6 mx-auto'>
                                    <a type='button' id='btnUploadBin' class='centered btnForm link-green' onclick='fncUploadBin(this)'>Atualizar</a>
                                </div>
                            </td>
                        </tr>
                    </table>
                </form>
            </div>
    
        </div>
    </div>

    </div> <!-- End of navOptions-->
</div>
`; // bodyHTML
    
    timerGetStatusID = null;

    function fncOnLoaded(){
        fncSetupRoutineGetStatus();
        createSocketsConnection();
        setInterval(sendOnSockets, 1000);
        // Fix BS-Toogle style only apply when included, so only include after loaded
        loadInclude([0, 'text/javascript', '/Resources/JS/bs_toogle.js', 'https://cdn.jsdelivr.net/gh/gitbrent/bootstrap4-toggle@3.6.1/js/bootstrap4-toggle.min.js']);
    }

    function fncSetupRoutineGetStatus(){
        $('#collapseStatus').on('hide.bs.collapse' , function () { fncStopRoutineGetStatus();  });
        $('#collapseStatus').on('shown.bs.collapse', function () { fncStartRoutineGetStatus(); });
    }

    function fncStartRoutineGetStatus(){
        fncRequestStatus();
        timerGetStatusID = setInterval(function() { fncRequestStatus(); }, 10000 );
    }

    function fncStopRoutineGetStatus(){
        if( timerGetStatusID ){
            clearTimeout( timerGetStatusID );
        }
    }

    function fncRequestStatus(){
        fncGetJSON('status.json', fncHandleStatusJSON);
    }

    var _jsonStatusFile = null;
    function fncHandleStatusJSON( file ){
        if( !file ){return;}
        _jsonStatusFile = file;

        var tab = document.getElementById('tableStatus');
        var tabBody = tab.tBodies.item(0); 
        var keys = Object.keys(_jsonStatusFile);
        if( keys.length > 0 ){
            tabBody.innerHTML = '';
        }else{
            return;
        }
        keys.forEach( function(key){
            var keyValue = String( _jsonStatusFile[key] );

            var row     = document.createElement('tr');
            row.id      = tab.rows.length;
            row.classList.add('d-flex');

            var cellLabel = document.createElement('td');
            cellLabel.classList.add('col-4');
            cellLabel.innerText = key;
            row.appendChild(cellLabel);

            var cellValue = document.createElement('td');
            cellValue.classList.add('col-8');
            cellValue.innerHTML = "<input class='text-center col-12' type='text' disabled value='" + keyValue + "'/>";
            row.appendChild(cellValue);
            
            tabBody.appendChild(row);
        });
    }

    // ---------------------------
    // Navbar options functions
    function fncToggleStatus(){
        if( $('#collapseStatus').is( ":hidden" ) ){
            $('#navOptions .collapse').collapse('hide');
            $('#collapseStatus').collapse('show');
            setTimeout( () => { fncScrollInto('collapseStatus'); }, 200 );
        }else{
            $('#collapseStatus').collapse('hide');
        }
    }
    
    function fncToggleControl(){
        if( $('#collapseControl').is( ":hidden" ) ){
            $('#navOptions .collapse').collapse('hide');
            $('#collapseControl').collapse('show');
            setTimeout(() => { fncScrollInto( 'collapseControl' ); }, 200);
        }else{
            $('#collapseControl').collapse('hide');
        }
    }

    function fncToggleNetwork(){
        if( $('#collapseSetupRede').is( ":hidden" ) ){
            $('#navOptions .collapse').collapse('hide');
            $('#collapseSetupRede').collapse('show');
            setTimeout(() => { fncScrollInto( 'PSWD' ); fncBtnRefresh_Click(); }, 200);
        }else{
            $('#collapseSetupRede').collapse('hide');
        }
    }

    function fncToggleFirmware(){
        if( $('#collapseFirmware').is( ":hidden" ) ){
            $('#navOptions .collapse').collapse('hide');
            $('#collapseFirmware').collapse('show');
            fncGetFirmwareInfo();
            setTimeout(() => { fncScrollInto( 'collapseFirmware' );  }, 200);
        }else{
            $('#collapseFirmware').collapse('hide');
        }
    }

    function fncApplyNetwork(){
        document.getElementById("btnSubmitWiFi").click();
    }

    function fncOnSwitchesChange(){
        var power = $('#chkPower').is(":checked");
        $( "#rangeSteering" ).prop( "disabled", (!power) || $('#chkAutoSteering').is(":checked") );
        $( "#rangeSpeed" ).prop( "disabled", (!power) || $('#chkAutoThrottle').is(":checked") );
    }
    
    
    // ---------------------------
    // WebSockets Setup
    var socketObj = null;
    var inSocketObj = null;
    var websocketHadConnection = 0;
    var logWebSocketsIn  = 0;
    var logWebSocketsOut = 0;
    
    function sendOnSockets(){
        var ouSocketObj          = new Object();  
        ouSocketObj.power        = +$('#chkPower').is(":checked");
        ouSocketObj.steeringMode = +$('#chkAutoSteering').is(":checked");
        ouSocketObj.throttleMode = +$('#chkAutoThrottle').is(":checked");
        ouSocketObj.speed        = +$('#rangeSpeed').val();
        ouSocketObj.steering     = +$('#rangeSteering').val();
        ouSocketObj.steeringGain = +$('#numSteeringGain').val();
        ouSocketObj.qtrMin       = +$('#numQtrMin').val();
        ouSocketObj.qtrMax       = +$('#numQtrMax').val();
        ouSocketObj = JSON.stringify( ouSocketObj );
        if( logWebSocketsOut ){
            console.log( "ws >> ", ouSocketObj );
        }
        if( socketObj && (socketObj.readyState==1) ){
            socketObj.send( ouSocketObj );
        }
    }

    function setValueIfKeyExists(pJson, pId, pKey){
        if( pJson && pJson.hasOwnProperty( pKey ) ) {
            $( pId ).val(+pJson[ pKey ]);
        }
    }

    function handleControlWebSocketsJson( pJson ){
        for(i=0; i<8; i++){
            setValueIfKeyExists( pJson, '#numQtr' + i, 'qtr' + i );
        }
        if( $('#chkAutoThrottle').is(":checked") ){
            setValueIfKeyExists(pJson, '#rangeSpeed', 'speed');
        }
        if( $('#chkAutoSteering').is(":checked") ){
            setValueIfKeyExists(pJson, '#rangeSteering', 'steering');
        }
    }

    function onSocketsReceived(event){
        inSocketObj = event.data;
        if( logWebSocketsIn ){
            console.log('ws << ', inSocketObj);
        }
        try{
            handleControlWebSocketsJson( JSON.parse(inSocketObj) );
        }catch(err){
            console.log( err.message );
        }
    }

    function onSocketsOpen(event){
        console.log("ws Open!");
        websocketHadConnection = 1;
        $('#lblWebSocketsStatus').text('Conectado');
    }
    function onSocketsClose(){
        $('#lblWebSocketsStatus').text('Desconectado');
        if(websocketHadConnection){
            websocketHadConnection = 0;
            console.log("ws Close!");
        }
    }
    function onSocketsError(event){
        $('#lblWebSocketsStatus').text('Desconectado');
        try{socketObj.close();}catch(err){}
        setTimeout(createSocketsConnection, 1000);
        if( websocketHadConnection ){
            console.log("ws Error!");
            console.log(event);
        }
    }

    function createSocketsConnection(){
        try{
            socketObj = new WebSocket('ws://'+ location.hostname +'/control');
            socketObj.addEventListener(   'open', onSocketsOpen);
            socketObj.addEventListener('message', onSocketsReceived);
            socketObj.addEventListener(  'close', onSocketsClose);
            socketObj.addEventListener(  'error', onSocketsError);
        }catch(err){
            //            
        }
    }

</script>


</head>

<body id='restrito-tecnicos'>

	<div class="master-wrap">
        
        <header class="wow fadeInDown animated" style="visibility: visible; animation-name: fadeInDown;">
            <div class="container-fluid">
                <div class="row" style="height: 150px">
                    <div class="col-12 my-auto">
                        <a target='_blank' rel='noopener noreferrer' href='/' class='logo'>
                            <div id='logo'></div>
                        </a>
                    </div>
                </div>
            </div>
        </header>

		<div class="title">
			<div class="container">
				<div class="row">
					<div class="col-12 text-center">
						<h1 id='pgTitle'></h1>
					</div>
				</div>
			</div>
        </div>
        
<div id='bodyHTML' style='margin-top: -50px;'></div>
<div class="container-fluid" style="bottom: 0; left: 0; right: 0; margin-left: 0; margin-right: 0; margin-bottom: 0; padding-left: 0; padding-right: 0; padding-bottom: 0; width: 100%;">
    <div class="copyright row">
        <div class="col-12 col-md-6 text-center mx-auto">
            <a href="http://www.navitastecnologia.com.br/" target="_blank">
                <img id='navitasLogo' alt='' width='80&#37' style='min-width: 150px;' src='/Resources/Fig/navitas.png'>
            </a>
        </div>
    </div>
</div>

</div> <!-- End of master-wrap-->

</body>
<script>_loadPage();</script>
</html>
)=====";
#pragma endregion // HTML_ROOT 
