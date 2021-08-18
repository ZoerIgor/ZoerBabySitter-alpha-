#include "LIB_Html.h"
#define DEBUG
// Информер
    RemainingTime::RemainingTime(String id, const short &timeInSec, String endMsg, byte priority)
    {
        _id = id;
        _timeInSec = timeInSec;
        _endMsg = endMsg;
        _priority = priority;
    }
    String RemainingTime::getContent()
    {
        return "<div style=\"font-size:10vw;padding-right:6vw;text-align:center\" id=\"" + _id + "\"></div><script>const SEC_IN_MIN_" + _id + " = 60;let timer_" + _id + ";let minutes_" + _id + " = Math.floor(" + String(_timeInSec, DEC) + " / SEC_IN_MIN_" + _id + ");let seconds_" + _id + " = " + String(_timeInSec, DEC) + " - (minutes_" + _id + " * SEC_IN_MIN_" + _id + ");let countdown_" + _id + " = minutes_" + _id + " * SEC_IN_MIN_" + _id + ";let view_" + _id + " = document.getElementById('" + _id + "');Countdown_" + _id + "();function Countdown_" + _id + "(){if (--countdown_" + _id + " == 0){clearTimeout(timer_" + _id + ");view_" + _id + ".innerHTML = '" + _endMsg + "';}else{let min_" + _id + ";let sec_" + _id + ";if (seconds_" + _id + "-- == 0){minutes_" + _id + "--;seconds_" + _id + " = SEC_IN_MIN_" + _id + " - 1;}if (minutes_" + _id + " < 10){min_" + _id + " = '0' + minutes_" + _id + ";}else{min_" + _id + " = minutes_" + _id + ";}if (seconds_" + _id + " < 10){sec_" + _id + " = '0' + seconds_" + _id + ";}else{sec_" + _id + " = seconds_" + _id + ";}view_" + _id + ".innerHTML = min_" + _id + " + ' : ' + sec_" + _id + ";timer_" + _id + " = setTimeout(Countdown_" + _id + ", 1000);}}</script>";
    }
    byte RemainingTime::getPriority()
    {
        return _priority;
    }
    int RemainingTime::getDurationInSec()
    {
        return _timeInSec;
    }
    byte Ticker::_spaceCountStatic = 1;
    short Ticker::_updateTimeStatic = 100;
    short Ticker::_pauseTimeStatic = 1000;
    short Ticker::_updateGeneralTimeStatic = UPDATE_TIME_IN_SEC;
    Ticker::Ticker(String id, String attachment, short visibleArea, byte priority)
    {
        _id = id;
        _attachment = attachment;
        _visibleArea = visibleArea;
        _priority = priority;
        _spaceCount = _spaceCountStatic;
        _updateTime = _updateTimeStatic;
        _pauseTime = _pauseTimeStatic;
    }
    Ticker::Ticker(String id, String attachment, short visibleArea, byte priority, byte spaceCount, short updateTime, short pauseTime)
    {
        _id = id;
        _attachment = attachment;
        _visibleArea = visibleArea;
        _priority = priority;
        _spaceCount = spaceCount;
        _updateTime = updateTime;
        _pauseTime = pauseTime;
    }
    void Ticker::setUpdateGeneralTimeInSec(short time)
    {
        _updateGeneralTimeStatic = time;
    }
    void Ticker::setStaticVar(byte spaceCount, short updateTime, short pauseTime)
    {
        _spaceCountStatic = spaceCount;
        _updateTimeStatic = updateTime;
        _pauseTimeStatic = pauseTime;
    }
    String Ticker::getContent()
    {
        return "<div id=\"" + _id + "\"></div><script>let source_" + _id + " = '" + _attachment + "';let sizeSource_" + _id + " = source_" + _id + ".length;let sizeView_" + _id + " = " + _visibleArea + ";let spaceCount_" + _id + " = " + _spaceCount + ";let endLoop_" + _id + " = false;let smallSourse_" + _id + " = true;let counter_" + _id + " = 0;let beginCursor_" + _id + " = 0;let endCursor_" + _id + " = 0;let standartTime_" + _id + " = " + _updateTime + ";let pausedTime_" + _id + " = " + _pauseTime + ";let updateTime_" + _id + " = standartTime_" + _id + ";let result_" + _id + " = '';const totalCount_" + _id + " = sizeView_" + _id + " + sizeSource_" + _id + ";UpdateView_" + _id + "();function UpdateView_" + _id + "(){result_" + _id + " = '';if (endLoop_" + _id + "){updateTime_" + _id + " = pausedTime_" + _id + ";endLoop_" + _id + " = false;}else{if (counter_" + _id + " == totalCount_" + _id + " - 1){counter_" + _id + " = 0;beginCursor_" + _id + " = 0;endCursor_" + _id + " = 0;updateTime_" + _id + " = standartTime_" + _id + ";smallSourse_" + _id + " = true;}if (counter_" + _id + " < sizeSource_" + _id + " || smallSourse_" + _id + "){for (let i = 0; i < sizeView_" + _id + " - counter_" + _id + "; i++){for (let i = 0; i < spaceCount_" + _id + "; i++){result_" + _id + " += '&nbsp';}}if (counter_" + _id + " < sizeSource_" + _id + " && smallSourse_" + _id + "){endCursor_" + _id + "++;}if (endCursor_" + _id + " > sizeView_" + _id + "){beginCursor_" + _id + "++;}for (let i = beginCursor_" + _id + "; i < endCursor_" + _id + "; i++){result_" + _id + " += source_" + _id + "[i];}if (sizeView_" + _id + " - counter_" + _id + " == 0 && sizeView_" + _id + " > sizeSource_" + _id + "){smallSourse_" + _id + " = false;}}else{let begin_" + _id + " = counter_" + _id + " - sizeView_" + _id + ";for (let i = begin_" + _id + "; i < sizeSource_" + _id + " - 1; i++){result_" + _id + " += source_" + _id + "[i + 1];}}if (result_" + _id + ".length == 1){endLoop_" + _id + " = true;}counter_" + _id + "++;}document.getElementById('" + _id + "').innerHTML = result_" + _id + ";setTimeout(UpdateView_" + _id + ", updateTime_" + _id + ");}</script>";
    }
    byte Ticker::getPriority()
    {
        return _priority;
    }
    int Ticker::getDurationInSec()
    {
        int one = (((_attachment.length() + (_visibleArea / _spaceCount)) * _updateTime) + _pauseTime);
        int all = (_updateGeneralTimeStatic * MILLIS_IN_SEC) / one;
        int total = ceil((all * one) / MILLIS_IN_SEC);
        float a = (total * 75) / 100;
        total = a;
        return total;
    }
    InfoQueue::Data::Data(Info &info)
    {
        _data = info.getContent();
        _priority = info.getPriority();
        _durationInSec = info.getDurationInSec();
    }
    String InfoQueue::Data::getContent()
    {
        return _data;
    }
    byte InfoQueue::Data::getPriority()
    {
        return _priority;
    }
    int InfoQueue::Data::getDurationInSec()
    {
        return _durationInSec;
    }
    bool InfoQueue::Compare::operator()(Data &dataA, Data &dataB)
    {
        return dataA.getPriority() < dataB.getPriority();
    }
    void InfoQueue::setAutoAddPriority(byte priority)
    {
        _autoAddPriority = priority;
    }
    void InfoQueue::setAutoClearPriority(byte priority)
    {
        _autoClearPriority = priority;
    }
    void InfoQueue::setEmptyQueueMessage(String message)
    {
        _queueEmpty = message;
    }
    void InfoQueue::setUpdateTimeInSec(short time)
    {
        _updateTime = time;
    }
    void InfoQueue::add(Info &info)
    {
        Data data(info);
        _pq.emplace(data);
    }
    void InfoQueue::add(Data &data)
    {
        _pq.emplace(data);
    }
    String InfoQueue::get()
    {
        if (!_pq.empty())
        {
            Data data = _pq.top();
            return data.getContent();
        }
        return _queueEmpty;
    }
    void InfoQueue::pop()
    {
        if (!_pq.empty())
        {
            _pq.pop();
        }
    }
    void InfoQueue::automatic()
    {
        if (!_pq.empty())
        {
            Data data = _pq.top();
            byte priority = data.getPriority();
            if (priority <= _autoClearPriority)
            {
                _pq.pop();
                if (priority <= _autoAddPriority)
                {
                    add(data);
                }
            }
        }
    }
    int InfoQueue::getDurationInSec()
    {
        if (!_pq.empty())
        {
            Data data = _pq.top();
            return data.getDurationInSec();
        }
        return _updateTime;
    }
// Заглушка кнопки
    const String buttonCap = "<td><button type=\"button\" align=\"left\" style=\"width:40vw; height:40vw; background:transparent; border-style:none;\"></button></td>";
    const String buttonColorCap = "<td><button type=\"button\" align=\"left\" style=\"width:40vw; height:40vw;\"></button></td>";
// Подсключаемые стили CSS
    Css::Css(String attachment)
    {
        this->_css = attachment;
    }
    String Css::get()
    {
        return _css;
    }
// Статическое начало страницы
    Html::Html(String title, String attachment, int refresh, short pageYOffset, bool animation, bool landscape)
    {
       this->_title = title;
       this->_attachment = attachment;
       this->_refresh = refresh;
       this-> _pageYOffset = pageYOffset;
       this-> _animation = animation;
       _landscape = landscape;
       _css = "";
    }
    void Html::setCss(String attachment)
    {
        _css = attachment;
    }
    String Html::get()
    {
        String generalAnimation;
        String h1Animation;
        String h2Animation;
        if(_animation)
        {
            generalAnimation = "animation:Visible 2s;-webkit-animation:Visible 2s;";
            h1Animation = "animation:HederH1Animatiom 2s;-webkit-animation:HederH1Animatiom 2s;";
            h2Animation = "animation:HederH2Animatiom 2s;-webkit-animation:HederH2Animatiom 2s;";
        }
        String html = "<!DOCTYPE html><html><head><title>" + _title + "</title><meta charset=\"UTF-8\"";
        if(_refresh != 0)
        {
            html += " http-equiv=\"refresh\" content=\"" + String(_refresh, DEC) + "\"";
        }
        html += "><meta name=\"viewport\" content=\"initial-scale=1, maximum-scale=1, user-scalable=no\"><style type=\"text/css\">*{box-sizing:Border-box;-moz-box-sizing:Border-box;-webkit-box-sizing:Border-box;outline:None;}body{--content-height:100%;}table{background:linear-gradient(to bottom, #FEFBE0 0%, #ffffff 100%);width:100%;height:80vh;justify-content:space-between;border-spacing:0px;-ms-user-select:None;-moz-user-select:None;-khtml-user-select:None;-webkit-user-select:None;}.TrHeader{vertical-align:Top;background:linear-gradient(to top, #FEFBE0 -20%,#44546A 15%, #44546A 70%, #ffffff 100%);height:60px;}.TrView{background:transparent;}td{padding:0;}h1,h2,h3,h4,h5,p,li,a,input,select,button,.TableView,.TableSelect,.InputQuadro,.TdPresentation,.TablePresentation{" + generalAnimation + "font-family:Calibri;font-weight:Normal;font-style:Italic;font-size:5vw;color:#1A4B78;margin-top:0;padding:0;}input,select,button,.TableView,.TableSelect,.InputQuadro,.InputString,.TdPresentation,.TablePresentation{margin-bottom:6vw;margin-left:3vw;margin-right:3vw;border-style:Outset;border-width:4px;border-color:#6E84A2;border-radius:15px;}select,.TableView,.TableSelect{width:86vw;height:17vw;padding-left:5vw;}select,.TableSelect{background:linear-gradient(to bottom, #A9B4C6 0%,#ffffff 100%);}.TableView{background:linear-gradient(to bottom, #70AF70 0%,#C0dCC0 90%);}.TablePresentation{width:86vw;height:0;border: 1px solid #6E84A2;border-radius:0px;}.ThPresentation{height:6vw;font-weight:bold;border: 1px solid #6E84A2;border-radius:0px;}.TdPresentation{height:6vw;padding-left:5vw;border: 1px solid #6E84A2;border-radius:0px;}h4,h5,a,span,li,button,.InputQuadro{font-style:Normal;}h4,h5,p{padding-left:6vw;padding-right:6vw;}h3,p{text-indent:10vw;}h1{" + h1Animation + "white-space:nowrap;color:White;font-family:Helvetica;font-size:7vw;margin-left:7vw;margin-bottom:18px;padding-top:18px;border-bottom:6px Groove Red;}h2{" + h2Animation + "white-space:nowrap;color:White;font-family:Times New Roman;text-align:Right;margin-right:7vw;margin-bottom:10px;border-bottom:6px Groove #1AB9FD;}h3{margin-top:-5vw;margin-bottom:0;text-align:Left;font-size:4vw;}h4{font-size:7vw;font-weight:Bold;margin-bottom:4vw;}h5{margin-bottom:1vw;font-size:6vw;text-decoration:Underline;}ol{margin-top:0;}li{margin-left:3vw;margin-right:3vw;padding-bottom:2vw;}p{text-align:Justify;}button{cursor:pointer;border-color:#C0C0C0;color:White;width:40vw;height:40vw;}.ListButton{cursor:pointer;border:none;background:transparent;width:80vw;height:5vw;font-family:Calibri;font-weight:Normal;font-size:5vw;color:#1A4B78;margin-top:0;margin-left:0;margin-bottom:0;padding-bottom:0vw;text-align:left;text-decoration: underline;}.DivBody{position:Absolute;top:0;left:0;right:0;}.InputString{background:linear-gradient(to top, #E1E6EC 0%, #ffffff 30%);width:86vw;height:17vw;text-indent:5vw;}.InputView{width:10vw;border:none;background:none;}.InputQuadro{width:40vw;height:40vw;font-size:10vw;text-align:Center;background:linear-gradient(to top, #E1E6EC 0%, #ffffff 30%);}.ButtonAnimationPosition{height:100%;position:Relative;}.ButtonAnimationPosition:active{}.ButtonSubmit,.ButtonCounterAction,.ButtonAction{overflow:Hidden;}.ButtonSubmit div,.ButtonCounterAction div,.ButtonAction div{position:Absolute;line-height:6vw;width:40vw;height:32vw;}.ButtonSubmit div:nth-child(2),.ButtonCounterAction div:nth-child(2),.ButtonAction div:nth-child(2){transition:All 0.2s ease;-webkit-transition:All 0.2s ease;-moz-transition:All 0.2s ease;margin-top:3.5vw;margin-left:-53%;width:210%;transform:Translate(-100%,0) skewX(-45deg);-webkit-transform:Translate(-100%,0) skewX(-45deg);-moz-transform:Translate(-100%,0) skewX(-45deg);}.ButtonSubmit div:nth-child(2){background:-moz-linear-gradient(to bottom,#4E617A 0,white 47%,#4E617A 100%);background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#4E617A),color-stop(47%,white),color-stop(100%,#4E617A));background:-webkit-linear-gradient(to bottom,#4E617A 0,white 47%,#4E617A 100%);background:-o-linear-gradient(to bottom,#4E617A 0,white 47%,#4E617A 100%);background:-ms-linear-gradient(to bottom,#4E617A 0,white 47%,#4E617A 100%);background:Linear-gradient(to bottom,#4E617A 0,white 47%,#4E617A 100%);progid:DXImageTransform.Microsoft.gradient(startColorstr=#4E617A,endColorstr=#4E617A,GradientType=0);}.ButtonCounterAction div:nth-child(2){background:-moz-linear-gradient(to bottom,#A34343 0,white 47%,#A34343 100%);background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#A34343),color-stop(47%,white),color-stop(100%,#A34343));background:-webkit-linear-gradient(to bottom,#A34343 0,white 47%,#A34343 100%);background:-o-linear-gradient(to bottom,#A34343 0,white 47%,#A34343 100%);background:-ms-linear-gradient(to bottom,#A34343 0,white 47%,#A34343 100%);background:Linear-gradient(to bottom, #A34343 0,white 47%,#A34343 100%);progid:DXImageTransform.Microsoft.gradient(startColorstr=#A34343,endColorstr=#A34343,GradientType=0);}.ButtonAction div:nth-child(2){background:-moz-linear-gradient(to bottom,#107049 0,white 47%,#107049 100%);background:-webkit-gradient(linear,left top,left bottom,color-stop(0,#107049),color-stop(47%,white),color-stop(100%,#107049));background:-webkit-linear-gradient(to bottom,#107049 0,white 47%,#107049 100%);background:-o-linear-gradient(to bottom,#107049 0,white 47%,#107049 100%);background:-ms-linear-gradient(to bottom,#107049 0,white 47%,#107049 100%);background:Linear-gradient(to bottom,#107049 0,white 47%,#107049 100%);progid:DXImageTransform.Microsoft.gradient(startColorstr=#107049,endColorstr=#107049,GradientType=0);}.ButtonSubmit div:nth-child(3),.ButtonCounterAction div:nth-child(3),.ButtonAction div:nth-child(3){left:-40vw;transition:Left 0.5s ease;-webkit-transition:Left 0.5s ease;-moz-transition:Left 0.5s ease;}.ButtonSubmit div:nth-child(3){color:#44546A;}.ButtonCounterAction div:nth-child(3){color:#A34343;}.ButtonAction div:nth-child(3){color:#107049;}.ButtonSubmit:active div:nth-child(2),.ButtonCounterAction:active div:nth-child(2),.ButtonAction:active div:nth-child(2){transition:All 0.5s ease;-webkit-transition:All 0.5s ease;-moz-transition:All 0.5s ease;transform:Translate(0,0) skewX(-45deg);-webkit-transform:Translate(0,0) skewX(-45deg);-moz-transform:Translate(0,0) skewX(-45deg);}.ButtonSubmit:active div:nth-child(3),.ButtonCounterAction:active div:nth-child(3),.ButtonAction:active div:nth-child(3){left:0;font-weight:Bold;transition:Left 0.8s ease;-webkit-transition:Left 0.8s ease;-moz-transition:Left 0.8s ease;}.slider{ -webkit-appearance:none; width:60vw; margin-top:6vw; margin-left:auto; margin-right:auto; height:0em; height:15px; border-radius:5px; outline:none; opacity:1; -webkit-transition: 0.2s; transition: opacity 0.2s; } .slider::-webkit-slider-thumb{ -webkit-appearance:none; appearance:none; width:35px; height:35px; border-radius:50%; border: 5px solid #44546A; background:#FFF; cursor:pointer; } .slider::-moz-range-thumb{ width:35px; height:35px; border-radius:50%; border: 5px solid #44546A; background:#FFF; cursor:pointer;}#blink{-webkit-animation:blink 3s linear infinite;animation:blink 3s linear infinite;}@-webkit-keyframes blink{0%{color:rgba(26,75,120,1);}50%{color:rgba(26,75,120,0);}100%{color:rgba(26,75,120,1);}}@keyframes blink{0%{color:rgba(26,75,120,1);}50%{ color:rgba(26,75,120,0);}100%{color:rgba(26,75,120,1);}}" + _css + "</style></head><body>";
        if (!_landscape)
        {
            html += "<script>window.onload = function(){window.screen.lockOrientation('portrait-primary');}</script>";
        }
        html += "<script>if(window.history.replaceState){window.history.replaceState( null, null, window.location.href );}</script><script>window.onfocus = function(){window.location.reload();}</script><div style=\"display: none\" id=\"hideAll\" class=\"DivBody\"><table><tr class=\"TrHeader\"><td colspan=\"2\"><h1>" + _title + "</h1><h2>" + _attachment + "<tr><td style=\"height:var(--content-height);\"></td></tr></table></div><script>setTimeout(Show, 5);function Show(){document.getElementById(\"hideAll\").style.display = \"block\";window.scrollTo(0," + String(_pageYOffset, DEC) + ")}</script></body></html>";
        return html;
    }
// Контекстный заголовок
    ContextHeader::ContextHeader(String header)
    {
        contextHeader = header + "</h2></td></tr><tr><td colspan=\"2\" style=\"height:6vw;\"></td></tr>";
    }
    String ContextHeader::get()
    {
        return contextHeader;
    }
// Ссылка в рамке
    ReferenceInFrame::ReferenceInFrame(String header, String protocol, String value)
    {
        referenceInFrame = "<tr><td colspan=\"2\" align=\"center\" valign=\"top\"><h3>" + header + "</h3><table class=\"TableSelect\"><tr class=\"TrView\"><td><span><a href=\"" + protocol + value + "\">" + value + "</a></span></td></tr></table></td></tr>";
    }
    ReferenceInFrame::ReferenceInFrame(String header, String protocol, String value, String mailSubject, String mailBody)
    {
        referenceInFrame = "<tr><td colspan=\"2\" align=\"center\" valign=\"top\"><h3>" + header + "</h3><table class=\"TableSelect\"><tr class=\"TrView\"><td><span><a href=\"" + protocol + value + "?subject=" + mailSubject + "&body=" + mailBody + "\">" + value + "</a></span></td></tr></table></td></tr>";
    }
    String ReferenceInFrame::get()
    {
        return referenceInFrame;
    }
// Отображение состояния
    StatusInFrame::StatusInFrame(String header, String value)
    {
        statusInFrame = "<tr><td colspan=\"2\" align=\"center\" valign=\"top\"><h3>" + header + "</h3><table class=\"TableView\"><tr class=\"TrView\"><td><label>" + value + "</label></td></tr></table></td></tr>";
    }
    StatusInFrame::StatusInFrame(String header, byte value, String measure)
    {
        statusInFrame = "<tr><td colspan=\"2\" align=\"center\" valign=\"top\"><h3>" + header + "</h3><table class=\"TableView\"><tr class=\"TrView\"><td><label>" + value + " " + measure + "</label></td></tr></table></td></tr>";
    }
    String StatusInFrame::get()
    {
        return statusInFrame;
    }
// Форма
    Form::Form(String id, String attachment)
    {
        form = form + "<form action=\"\" method=\"POST\" id=\"" + id + "\">" + attachment + "</form>";
    }
    String Form::get()
    {
        return form;
    }
// Отображение блока
    ShowHideBlock::ShowHideBlock(String attachment, String blockId, Checkbox &checkbox, bool hide)
    {
        this->blockId = blockId;
        this->attachment = "";
        this->hide = hide;
        String ifTrue;
        String ifFalse;
        if(hide)
        {
            ifTrue = "\"\"";
            ifFalse = "\"none\"";
        }
        else
        {
            ifTrue = "\"none\"";
            ifFalse = "\"\"";
        }
        showHideBlock = Before() + "document.getElementById('" + checkbox.getId() + "').addEventListener(\"click\", ShowHide);function ShowHide(){if (document.getElementById('" + checkbox.getId() + "').checked){document.getElementById(\"" + blockId + "\").style.display = " + ifTrue + ";}else{document.getElementById(\"" + blockId + "\").style.display = " + ifFalse + ";}}" + After();
    }
    ShowHideBlock::ShowHideBlock(String attachment, String blockId, bool hide)
    {
        this->blockId = blockId;
        this->attachment = attachment;
        this->hide = hide;
        showHideBlock = Before() + After();
    }
    ShowHideBlock::ShowHideBlock(Button &button, String blockId, String titleShow, bool hide)
    {
        String firstTitle;
        String secondTitle;
        if(hide)
        {
            firstTitle = button.getTitle();
            secondTitle = titleShow;
        }
        else
        {
            firstTitle = titleShow;
            secondTitle = button.getTitle();
        }
        showHideBlock = "<script>var hide = false;var switchButton = document.getElementById('" + button.getId() + "');var buttonTitle1 = document.getElementById('" + button.getId() + "_1');var buttonTitle2 = document.getElementById('" + button.getId() + "_2');switchButton.addEventListener('click', ShowHide);function ShowHide(){hide = !hide;if(!hide){document.getElementById(\"" + blockId + "\").style.display = \"none\";buttonTitle1.innerHTML = '" + firstTitle + "';buttonTitle2.innerHTML = '" + firstTitle + "';buttonTitle1.style.paddingTop = \"" + button.getPadding(firstTitle) + "vw\";buttonTitle2.style.paddingTop = \"" + button.getPadding(firstTitle) + "vw\";}else{document.getElementById(\"" + blockId + "\").style.display = \"\";buttonTitle1.innerHTML = '" + secondTitle + "';buttonTitle2.innerHTML = '" + secondTitle + "';buttonTitle1.style.paddingTop = \"" + button.getPadding(secondTitle) + "vw\";buttonTitle2.style.paddingTop = \"" + button.getPadding(secondTitle) + "vw\";}};</script>";
    }
    ShowHideBlock::ShowHideBlock(String attachment, String blockId, Radio &radio, String formId, bool hide)
    {
        this->blockId = blockId;
        this->attachment = attachment;
        this->hide = hide;
        showHideBlock = Before() + "var radios = document.getElementsByTagName('input');for(var i = 0; i < radios.length; i++) {radios[i].addEventListener('DOMContentLoaded', ShowHide);radios[i].addEventListener('click', ShowHide);function ShowHide() {if(this.name == '" + radio.getId() + "'){if(this.value == '" + radio.getValue() + "'){document.getElementById(\"" + blockId + "\").style.display = \"\";} else {document.getElementById(\"" + blockId + "\").style.display = \"none\";}}}}" + After();
    }
    ShowHideBlock::ShowHideBlock(Radio &radio, String hideId, bool show)
    {
        String strShow = "";
        if (!show)
        {
            strShow = "none";
        }
        showHideBlock = "<script>var radios = document.getElementsByTagName('input');for(var i = 0; i < radios.length; i++) {radios[i].addEventListener('DOMContentLoaded', ShowHide_" + hideId + ");radios[i].addEventListener('click', ShowHide_" + hideId + ");function ShowHide_" + hideId + "() {if(this.name == '" + radio.getId() + "'){if(this.value == '" + radio.getValue() + "'){document.getElementById(\"" + hideId + "\").style.display = \"none\";} else {document.getElementById(\"" + hideId + "\").style.display = \"" + strShow + "\";}}}}</script>";
    }
    String ShowHideBlock::Before()
    {
        String before = "<tr><td colspan=\"2\" align=\"center\" valign=\"top\"><table style=\"height:0; background:transparent;" + View() + "\" id=\"" + blockId + "\"><tr><td align=\"center\" valign=\"top\">" + attachment + "</td></tr></table><script>";
        return before;
    }
    String ShowHideBlock::After()
    {
        return "</script></td></tr>";
    }
    String ShowHideBlock::View()
    {
        String view = "";
        if(hide)
        {
            view = "; display:none";
        }
        return view;
    }
    String ShowHideBlock::get()
    {
        return showHideBlock;
    }
// Контейнер переключателей
    CheckRadioContainer::CheckRadioContainer(String lable, String attachment)
    {
        checkRadioContainer = "<tr><td colspan=\"2\" align=\"center\" valign=\"top\"><h3>" + lable + "</h3><table class=\"TableSelect\"><tr class=\"TrView\"><td colspan=\"2\"><div style=\"margin-top:3vw;\"></div></td></tr>" + attachment + "</table></td></tr>";
    }
    CheckRadioContainer::CheckRadioContainer(String lable, String id, String attachment)
    {
        checkRadioContainer = "<tr><td id=\"" + id + "\" colspan=\"2\" align=\"center\" valign=\"top\"><h3>" + lable + "</h3><table class=\"TableSelect\"><tr class=\"TrView\"><td colspan=\"2\"><div style=\"margin-top:3vw;\"></div></td></tr>" + attachment + "</table></td></tr>";
    }
    String CheckRadioContainer::get()
    {
        return checkRadioContainer;
    }
// Флажок
    Checkbox::Checkbox(String name, String form, bool checked, String header)
    {
        this->name = name;
        _script = "";
        checkbox = "<tr class=\"TrView\"><td style=\"width:10vw;\"><input name=\"" + name + "\" id=\"" + name + "\" form=\"" + form + "\" type=\"checkbox\" onclick=\"ChangeRequired" + name + "()\" ";
        if(checked)
        {
            checkbox += "checked ";
        }
        checkbox += "style=\"transform:Scale(2); margin-top:3vw;\"/></td><td><div style=\"margin-top:-3vw;\"><lable style=\"padding-left:4vw; display:block\">" + header + "</lable></div></td></tr>";
    }
    void Checkbox::setRequiredFalse(String idInputs[], byte size)
    {
        String multipleIf = "";
        for(byte i = 0; i < size; i++)
        {
            multipleIf += "document.getElementById('" + idInputs[i] + "').required=true;";
        }
        String multipleElse = "";
        for(byte i = 0; i < size; i++)
        {
            multipleElse += "document.getElementById('" + idInputs[i] + "').required=false;";
        }
        _script += "<script>function ChangeRequired" + name + "(){if(document.getElementById('" + name + "').checked){" + multipleIf + "}else{" + multipleElse + "}}</script>";
    }
    String Checkbox::get()
    {
        return checkbox + _script;
    }
    String Checkbox::getId()
    {
        return name;
    }
// Переключатель
    Radio::Radio(String name, String value, String form, bool checked, String header)
    {
        this->name = name;
        this->value = value;
        radio = "<tr class=\"TrView\"><td style=\"width:10vw;\"><input type=\"radio\" name=\"" + name + "\" id=\"" + value + "\" value=\"" + value + "\" form=\"" + form + "\" ";
        if(checked)
        {
            radio = radio + "checked ";
        }
        radio = radio + "style=\"transform:Scale(2); margin-top:3vw;\"/></td><td><div style=\"margin-top:-3vw; padding-left:4vw\"\"><label>" + header + "</label></div></td></tr>";
    }
    String Radio::get()
    {
        return radio;
    }
    String Radio::getId()
    {
        return name;
    }
    String Radio::getValue()
    {
        return value;
    }
// Строчное поле ввода
    LineInputField::LineInputField(String header, String id, String formId, String value, String type, bool required, String pattern, String onKeyUp, String maxLenght, String placeHolder, String title)
    {
        this->_header = header;
        this->_id = id;
        this->_formId = formId;
        this->_value = value;
        this->_type = type;
        this->_required = required;
        this->_pattern = pattern;
        this->_onKeyUp = onKeyUp;
        this->_maxLenght = maxLenght;
        this->_placeHolder = placeHolder;
        this->_title = title;
        _encrypt = "";
    }
    LineInputField::LineInputField(String id, String formId, String value)
    {
        this->_id = id;
        this->_formId = formId;
        this->_value = value;
    }
    void LineInputField::setEncrypt(String attachment)
    {
        _encrypt = attachment;
    }
    String LineInputField::getHide()
    {
        return "<tr><td colspan=\"2\" align=\"center\" valign=\"top\"><input id=\"" + _id + "\" name=\"" + _id + "\" form=\"" + _formId + "\" value=\"" + _value + "\" class=\"InputString\" type=\"hidden\"></td></tr>";
    }
    String LineInputField::get()
    {
        _lineInputField = "<tr id=\"TR_" + _id + "\"><td colspan=\"2\" align=\"center\" valign=\"top\"><h3>" + _header + "</h3><input id=\"" + _id + "\" name=\"" + _id + "\" form=\"" + _formId + "\" value=\"" + _value + "\" class=\"InputString\" type=\"" + _type + "\"";
        if(_type == "password")
        {
           _lineInputField += " style=\"padding-right:15vw\"";
        }
        if(_required)
        {
            _lineInputField += " required";
        }
        if (_pattern != "")
        {
            _lineInputField += " pattern =\"" + _pattern + "\"";
        }
        if (_onKeyUp != "")
        {
            _lineInputField += " onkeyup=\"" + _onKeyUp + "\"";
        }
        if (_maxLenght != "")
        {
            _lineInputField += " maxlength=\"" + _maxLenght + "\"";
        }
        if (_placeHolder != "")
        {
            _lineInputField += " placeholder=\"" + _placeHolder + "\"";
        }
        if (_title != "")
        {
            _lineInputField += " title=\"" + _title + "\"";
        }
        _lineInputField += " oninput=\"ChangeSize();\">";
        if(_type == "password")
        {
           _lineInputField += "<div style=\" margin-top:-18vw; margin-bottom: 10vw; margin-left:70vw\"><a href=\"\" class=\"password-control\" onclick=\"return show_hide_password(this);\"></a></div><script>function show_hide_password(target){var input = document.getElementById('" + _id + "');if (input.getAttribute('type') == 'password') {target.classList.add('view');input.setAttribute('type', 'text');} else {target.classList.remove('view');input.setAttribute('type', 'password');}return false;}" + _encrypt + "</script>";
        }
        _lineInputField += "</td></tr>";
        return _lineInputField;
    }
    String LineInputField::getId()
    {
        return _id;
    }
// Две колонки
    TwoCol::TwoCol(String attachment)
    {
        twoCol = "<tr>" + attachment + "</tr>";
    }
    String TwoCol::get()
    {
        return twoCol;
    }
// Кнопка
    Button::Button(String align, String id, String formId, String type, String title)
    {
        #define COLOR_RED "#A34343"
        #define COLOR_GREEN "#107049"
        #define COLOR_BLUE "#4E617A"
        this->id = id;
        this->formId = formId;
        this->title = title;
        this->beginScript = "";
        this->endScript = "";
        String color = "";
        if(align == "right")
        {
            align = "left";
        }else
        {
            align = "right";
        }
        if(type == "ButtonSubmit")
        {
            color = COLOR_BLUE;
        }
        else if(type == "ButtonCounterAction")
        {
            color = COLOR_RED;
        }
        else if(type == "ButtonAction")
        {
            color = COLOR_GREEN;
        }
        button = "<td align=\"" + align + "\" valign=\"top\"><button type=\"submit\" onclick=\"TransferPosition_" + id + "(); FreeFormInput_" + id + "();\" onSubmit=\"window.location.reload();\" name=\"" + id + "\" id =\"" + id +"\" form=\"" + formId + "\" value=\"1\" style=\"background:" + color + "\"><div id=\"" + id + "_1\" class=\"ButtonAnimationPosition " + type + "\"><div id=\"" + id + "_2\" style=\"padding-top:" + getPadding(title) + "vw\">" + title + "</div><div></div><div id=\"" + id + "_3\" style=\"padding-top:" + getPadding(title) + "vw\">" + title + "</div></div></button></td>";
    }
    void Button::setWindowScroll()
    {
        button += "<input type=\"hidden\" form=\"" + formId + "\" id=\"SCROLL_" + id + "\" name=\"SCROLL_" + id + "\" value=\"0\"><script>function TransferPosition_" + id + "(){document.getElementById('SCROLL_" + id +"').value = window.pageYOffset || document.documentElement.scrollTop;}</script>";
    }
    void Button::setFreeFormInput(String idInput, String value)
    {
        this->idInput = idInput;
        beginScript += "<input type=\"hidden\" form=\"" + formId + "\" id=\"" + idInput + "_" + id + "\" name=\"" + idInput + "_" + id + "\" value=\"" + value + "\">";
        endScript += "document.getElementById('" + idInput + "_" + id + "').value = document.getElementById('" + idInput + "').value;";
    }
    void Button::setAlert(String alert)
    {
        button += "<script>alert(\"" + alert + "\");</script>";
    }
    String Button::get()
    {
        return button + beginScript + "<script>function FreeFormInput_" + id + "(){" + endScript + "}</script>";
    }
    String Button::getId()
    {
        return id;
    }
    String Button::getTitle()
    {
        return title;
    }
    float Button::getPadding(String _title)
    {
        #define GROWTH 3
        bool write = false;
        float padding = 16.5;
        byte counter = 0;
        String br = "";
        for(int i = 0; i < _title.length(); i++)
        {
            if(title[i] == '<')
            {
                write = true;
            }
            if(write)
            {
                br = br + _title[i];
                if(_title[i] == '>')
                {
                    if(br == "<br>" || br == "<BR>")
                    {
                        counter++;
                    }
                    write = false;
                    br = "";
                }
            }
        }
        padding = padding - GROWTH * counter;
        return padding;
    }
// Квадратное поле ввода
    QuadroInputField::QuadroInputField(String align, String name, String form, String value, bool required, String maxLenght, String min, String max, String placeHolder, String onKeyUp, String onChange, String script)
    {
        if(align == "right")
        {
            align = "left";
        }else
        {
            align = "right";
        }
        quadroInputField = "<td align=\"" + align + "\" valign=\"top\"><input class=\"InputQuadro\" name=\"" + name + "\" form=\"" + form + "\" value=\"" + value + "\" ";
        if(required)
        {
            quadroInputField += "required ";
        }
        quadroInputField = quadroInputField + "type=\"text\" maxlength=\"" + maxLenght + "\" min=\"" + min + "\" max=\"" + max + "\" placeholder=\"" + placeHolder + "\" onkeyup=\"" + onKeyUp + ";\" onchange=\"" + onChange + ";\"><script>" + script + "</script></td>";
    }
    String QuadroInputField::get()
    {
        return quadroInputField;
    }
// Выпадающий список
    Select::Select(String formId, String ownId, String targetId, String title)
    {
        this->_ownId = ownId;
        this->_targetId = targetId;
        _firstScript = false;
        _select = "<h3>" + title +"</h3><select form=\"" + formId + "\" value=\"1\" name=\"" + ownId + "\" id=\"" + ownId + "\" onchange=\"Change" + ownId + "();\">";
    }
    void Select::setOption(String value, String title, bool selected)
    {
        _select += "<option value=\"" + value + "\"";
        if(selected)
        {
            _select += " selected";
        }
        _select += ">&ensp;" + title + "</option>";
    }
    String Select::getSetAttribute(String atributeName, String atributevalue)
    {
        return "input.setAttribute(\"" + atributeName + "\", \"" + atributevalue + "\");";
    }
    String Select::getSetAttribute(String row, String atributeName, String atributevalue)
    {
        return "inputTr.setAttribute(\"" + atributeName + "\", \"" + atributevalue + "\");";
    }
    String Select::getRemoveAttribute(String nameAttribute)
    {
        return "inputTr.removeAttribute(\"" + nameAttribute + "\");";
    }
    void Select::setOptionScript(String value, String attachment)
    {
        if(!_firstScript)
        {
            _firstScript = true;
            _script += "if";
        }
        else
        {
             _script += "else if";
        }
        _script += "(selectValue == \"" + value + "\"){" + attachment + "}";
    }
    String Select::get()
    {
        return "<tr><td id=\"CONTAINER_" + _ownId + "\" colspan=\"2\" align=\"center\" valign=\"top\">" + _select + "</select></td><script>function Change" + _ownId + "(){var select = document.getElementById(\"" + _ownId + "\");var selectValue = select.options[select.selectedIndex].value;var inputTr = document.getElementById(\"TR_" + _targetId + "\");var input = document.getElementById(\"" + _targetId + "\");select.setAttribute(\"value\", selectValue);" + _script + "}window.onload = Change" + _ownId + ";</script></tr>";
    }
// Ползунок
    Range::Range(String lable, String form, String id, int min, int max, int value)
    {
        float x = (value - min) * (100.00 / (max - min));
        range = "<tr><td id=\"CONTAINER_" + id + "\" colspan=\"2\" align=\"center\" valign=\"top\"><table class=\"TableSelect\"><tr class=\"TrView\"><h3>" + lable + "</h3><td style=\"width:10vw;\"><div align=\"center\" style=\"margin-left:-2vw;\"><input type=\"text\" readonly form=\"" + form + "\" name=\"" + id + "\" id=\"" + id + "Value\" class=\"InputView\" style=\"margin-bottom:0vw; \"></div></td><td><input type=\"range\" id=\"" + id + "\" min=\"" + min + "\" max=\"" + max + "\" value=\"" + value + "\" class=\"slider\" style=\"background: linear-gradient(90deg, #44546A " + x + "%, #fff " + x + "%)\"><script>var slider" + id + " = document.getElementById(\"" + id + "\");var output" + id +" = document.getElementById(\"" + id + "Value\");output" + id + ".value = slider" + id + ".value;slider" + id + ".addEventListener(\"mousemove\", CalcRange" + id +");slider" + id + ".addEventListener(\"touchmove\", CalcRange" + id + ");function CalcRange" + id + "(){output" + id + ".value = slider" + id +".value;var x = (slider" + id + ".value - slider" + id + ".min) * (100 / (slider" + id + ".max - slider" + id + ".min));var color = 'linear-gradient(90deg, #44546A ' + x + '%, #fff ' + x + '%)';slider" + id + ".style.background = color;}</script></td></tr></table></td></tr>";
    }
    String Range::get()
    {
        return range;
    }
// Контейнер списка
    ListContainer::ListContainer(String attachment)
    {
        listContainer = "<tr><td colspan=\"2\"><ol type=\"1\">" + attachment + "</ol></td></tr>";
    }
    String ListContainer::get()
    {
        return listContainer;
    }
// Тело списка
    List::List(String id, String header)
    {
        list = "<li><button name=\"" + id + "\" id=\"" + id + "\" value=\"1\" form=\"FORM\" class=\"ListButton\">" + header + "</button></li>";
    }
    String List::get()
    {
        return list;
    }
// Контейнер для текста
    TextContainer::TextContainer(String attachment)
    {
        textContainer = "<tr><td colspan=\"2\">" + attachment + "</td></tr>";
    }
    String TextContainer::get()
    {
        return textContainer;
    }
// Заголовок текста
    TextHeader::TextHeader(String header)
    {
        textHeader = "<h4>" + header + "</h4>";
    }
    String TextHeader::get()
    {
        return textHeader;
    }
// Подзаголовок текста
    TextSubHeader::TextSubHeader(String header)
    {
        textSubHeader = "<h5>" + header + "</h5>";
    }
    String TextSubHeader::get()
    {
        return textSubHeader;
    }
// Текст
    Text::Text(String newText)
    {
        text = "<p>" + newText + "</p>";
    }
    String Text::get()
    {
        return text;
    }
// Таблица
    Table::Table()
    {
        table = "";
        openTag = "<th class=\"ThPresentation\">";
        closeTag = "</th>";
    }
    void Table::set(String row)
    {
        bool verification = false;
        bool addColumn = false;
        String column = "";
        String container = "";
        table += "<tr>";
        for(int i = 0; i < row.length(); i++)
        {
            if(row[i] == '<')
            {
                verification = true;
            }
            if(verification)
            {
                container = container + row[i];
                if(container == "<td>")
                {
                    addColumn = true;
                    verification = false;
                }
                if(addColumn)
                {
                    table = table + openTag + column + closeTag;
                    column = "";
                    addColumn = false;
                }
            }
            else
            {
                column += row[i];
            }
        }
        table = table + openTag + column + closeTag;
        openTag = "<td class=\"TdPresentation\">";
        closeTag = "</td>";
    }
    String Table::get()
    {
        table = "<tr><td colspan=\"2\" align=\"center\"><table class=\"TablePresentation\">" + table + "</table></td></tr>";
        return table;
    }
// Диалоговое окно
    Alert::Alert(String message)
    {
        this->_alert = message;
    }
    void Alert::set(String message)
    {
        this->_alert = message;
    }
    String Alert::get()
    {
        _alert = "<script>alert(\"" + _alert + "\");</script>";
        return _alert;
    }