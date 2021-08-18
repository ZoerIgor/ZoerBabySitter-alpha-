#include "FUNC_Html.h"
#define DEBUG
#define LIMIT_MIN 1
#define LIMIT_MAX 9
#define WORK_TIME_MIN 1
#define WORK_TIME_MAX 60
#define DEBUG
bool animation = true;
bool animationMain = true;
bool reloadPage = false;
bool breakAction = false;
bool loadNextPage = false;
short pageYOffset = 0;
short pageOffsetMain = 0;

String header = "Zoer Baby Sitter";
Css CssSelect("select{-moz-appearance: none;-webkit-appearance: none;appearance: none;background-color: #fff;background-image: url('data:image/svg+xml;charset=US-ASCII,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20width%3D%22292.4%22%20height%3D%22292.4%22%3E%3Cpath%20fill%3D%22%23007CB2%22%20d%3D%22M287%2069.4a17.6%2017.6%200%200%200-13-5.4H18.4c-5%200-9.3%201.8-12.9%205.4A17.6%2017.6%200%200%200%200%2082.2c0%205%201.8%209.3%205.4%2012.9l128%20127.9c3.6%203.6%207.8%205.4%2012.8%205.4s9.2-1.8%2012.8-5.4L287%2095c3.5-3.5%205.4-7.8%205.4-12.8%200-5-1.9-9.2-5.5-12.8z%22%2F%3E%3C%2Fsvg%3E'),linear-gradient(to bottom, #A9B4C6 0%,#ffffff 100%);background-repeat: no-repeat, repeat;background-position: right 5vw top 50%, 0 0;background-size: 4vw auto, 100%;}");
Css CssAnimation("@keyframes Visible{from{opacity:0.7;}to{opacity:1;}}@-webkit-keyframes Visible{from{opacity:0.7;}to{opacity:1;}}@keyframes HederH1Animatiom{from{margin-left:30%;width:70%;opacity:0;}to{margin-left:7%;width:93%;opacity:1;}}@-webkit-keyframes HederH1Animatiom{from{margin-left:30%;width:70%;opacity:0;}to{margin-left:7%;width:93%;opacity:1;}}@keyframes HederH2Animatiom{from{margin-right:30%;width:70%;opacity:0;}to{margin-right:7%;width:93%;opacity:1;}}@-webkit-keyframes HederH2Animatiom{from{margin-right:30%;width:70%;opacity:0;}to{margin-right:7%;width:93%;opacity:1;}}");
Css CssSlider(".slider{-webkit-appearance:none;width:64vw;margin-top:6vw;margin-left:auto;margin-right:auto;height:0em;height:15px;border-radius:5px;outline:none;}.slider::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:35px;height:35px;border-radius:50%;border: 5px solid #44546A;background:#FFF;cursor:pointer;}.slider::-moz-range-thumb{width:35px;height:35px;border-radius:50%;border: 5px solid #44546A;background:#FFF;cursor:pointer;}");
Css CssPassword(".password-control{position: inherit;display: inline-block;width: 5vw;height: 7vw;background: url('data:image/jpeg;base64,/9j/4AAQSkZJRgABAgEASABIAAD/2wBDAAEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQECAgICAgICAgICAgMDAwMDAwMDAwP/2wBDAQEBAQEBAQEBAQECAgECAgMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwP/wAARCAAPABoDAREAAhEBAxEB/8QAFwAAAwEAAAAAAAAAAAAAAAAABgcJCv/EADEQAAEEAgEBBAYLAAAAAAAAAAMCBAUGBwgBCQARNTcTFhc2OFQSFRkzNFVXY2RlZv/EABkBAAMAAwAAAAAAAAAAAAAAAAQFCAYHCf/EADURAAIBAwICBwYEBwAAAAAAAAECAwQFBgcREhMAFCEiMjM1CBc0UmJjFSMxURgkU1VWYWT/2gAMAwEAAhEDEQA/AKs9SPrW3Idss2DdOJkVehq29dwVuzk3btX01PS7IpGspFY3E+A4YxkGyONQeZlSCOXheOVsvQCQNy4sXSnQCgaipMizuAyzyqHjpCSFRT2q05BBZyNjygQqjsk4iSi87dd/awuiXO4YhpdUiCmp3Mc1wADPI6nZ0pQwKpGp3UzkF3PbFwKFkcRVp5rRWrxiTD26O62yIdys306Ju4rBF2tCsf45krKN4qswc7ZrcCUkZaVkpdiRiDlD0a3rlCeEjaJMFazBnWWVdvvd9wHT+0nA7fO0RRovzp1j25jrHEVCqqsHPcIRSdy5VgAPdfgdBd8axfVbVi/jVO7UqVAkSf8Al6Z5Q3KjeWYOzuzqY12kBkYDZYgyErak9Qfbfpi7NXTWzN93lNkcV48s7eDl42wvzvrKmsybJhNQtpoNnmzPJqLkC12VbOPqZ+7dxqV8rapUFXc7S4uGmOE6u4lb8rx23pabxVQl1ZABHzFJR45o0ARgHVl5qKr7bOQ3gOPWnWzUv2f8/uuB5fd5L9jtFUCN1lYtLynVZI5qeWQs6sYnRuRI7xA7xgofzBoK+1P0c/WqM8k/bx4dI+6X5B9x5jf57xP9rtMvuc1D/sD+odT8S+b8/wCvkfe8v/fS1v4h9JP8qj9J/EfC3k/0/wBPif8Am836ekZ+pno7pvlS9XPK+uu2mqGN8xml5X2o4YuGd8YVeCsFsaujinX8aQth4NR70aQGRMizdiQydPPpEIpmf05D740k1DzuzW6gsuUYVequwhF6vVRUdRI6RkDgDdzaaELtwMpLqvYA68IWV9ftItLcjvF1yPB9SsboMpMr9boZ7hSRRyTAkSMu8m9PUFgRKjqI3fdmMT8ZcBmNvrXQ7fhOs7k9O+o5T3XxjAU6BwhkKTyPEQcnc2wZQrHHk1I1yLROxl2MqwDWRg5bGdtXMnyUjJLUildzGDB6K5UOQVmB6oz0en9XJK9XCsDusRKgzortwNEODYOrBWWPhEhcAdFFVqbcrNdMSt+qeh9NcdWbfDBHQVLVUcbzgOVpnaNOYs55gJjZWdGl4jEI2J6L2mach2F2du+aepvstr3rzJzlpBZb1haTzdjKt5ekOCsI40DU3NfNbDlxlVhVrhmAK3hzTXMehHHAkEIl4lpX522MYhb7BpFid0ukMcJjhq1pKh6Ze8weQPyx1iQycRIUCLjJ7SBwdEdr0uTNdQbtlftAZ7ZLJUzVAlqKBq+kirW3VTHCYzMeqwiLgVS7NPywO6GYSjRp6tdN35nU34bPVr3rxv8ACt8z4z5Vf234T+R2lnreqvyXr1bmeXP6j+3h+I+34vp6XN1DQr58b9B5XnUvpH7+P4P73g+vp//Z') 0 0 no-repeat;background-position: right 0 top 50%, 0 0;background-size: 5vw auto, 100%;}.password-control.view{background: url('data:image/jpeg;base64,/9j/4AAQSkZJRgABAgEASABIAAD/2wBDAAEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQECAgICAgICAgICAgMDAwMDAwMDAwP/2wBDAQEBAQEBAQEBAQECAgECAgMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwP/wAARCAAUABoDAREAAhEBAxEB/8QAGAAAAwEBAAAAAAAAAAAAAAAABwkKCAX/xAA4EAAABAMFBQQHCQAAAAAAAAADBAUGAQIHCBMUFhcACREVGBIhMjMZIiQmNDVUJTc4VVhhYmVm/8QAGQEBAQEAAwAAAAAAAAAAAAAACAcGAwQJ/8QAOREAAQIEAgcFBgQHAAAAAAAAAgEDBAYREgUTAAcUFRYhMiIjMUFRCBcYQlJjJCVhcTM0NTZWV2T/2gAMAwEAAhEDEQA/AKpN4FvVqQWI4xYqYmy1VrsbJAnAqfpynInJTTJHAoCklV/rsgByZJlNgzQFLEAQhTxkOMs8YAAzyDxsmrPU1jmsH8xdd2KXBJUV4huJxU8RZCqXUXkRqqAK1SpEijodddPtGSxql/KGGN4zgQoSQwGggyJJUTiHKFZVOYtiKuElFVAFUPTDSLXTfQ1MpNNanNuuy/ZvotMjBvMsmVETCqOBFiiwDMgOY5IrpD4XyyYaICyigwHUCZw5JGSIAEYihSz0KIl3ULhONpJwQeM4rj+ZlKTBXd94K2lpNApIXJaAQitbi5LSSQc3+1VMEt+8NzEJdwKVVaR9AiQs/DrzR0rwfcQSFUUbnAM0VLA7QovVb+8AYzxtQ0BCteVaVaeIaETIq9K2K20tSYTeOvRQSgiKLXK00Xg4DymwE+oBZVHFabRNGTsiSlDBnVuYKU0HGfgidWeIwMoTKUkYKEVEOEoxDxkLxi0hVOEgFsQXiZUUSJiREFccRW4dFsWnahNdGDYnrBk1vWXMpwUK0AnCQ7QFDtE+QILcfiiZhHDDEIZLBwZm4jLRC7FKKOIpUO4or9SB5GK84P4X6nxeR/Pw/vsYrD+hfGnh5+n7/po2Mxv608K+KeHr+36+GkV28J3Xtomnlo51O5NPnqg0iqq5HA9BK7vVYlCTGAVM4pdcs1cHIPLdt0Jrk5BZgz8Q4hKhYMMMmHMdngRlfOrHXBK+JyrBwLrQw2OQTQNJBtD2nlSgN7ICdauLSoVq2SqpqjaZi+U2uz2e55wae8QxOHeONlnEX3H1xB86DDItXHdvdXk2jQ1VHKUdFBFoVdXJRuROvtBK7ulvO217WimVI7PtEE1rLtJLLrscpBDddU1MgkFTaDXKsdOzQ07gnQDQYchxmtEQsIYgXnBOHALwQIKaInLcyS5BxMFJGARkdM2IG4ETiDbZG3DipKhwkK+iWXpzGKiUJBuQgbKiKSJtuc5Nm7EIPEtZk14fhkl4S205B4U86Lb0WQgitx8bDEuZlklDgoNRUrVFx0Kkgkh6q7Rfe9Et/VgXLMDGUVBEfjtTRC6wqFBktBbLPRERGaBd8vw9cCBt0orl0KJ7DzwnOiTC4cIIYxDsRSGCx2G6n9WmBw034gAxEMwVQFUI3HTM3VZZSvbUVOy5KAlLiUR56DaZMMxj2htdEzxmr7CHDg4yJChmig20y22DKREQVO6E0bVy1auKpWCJHyWij0SC5+sWu34Qumb5pP8AMPzL4r7uP898R/YbFv31w/8AguHf1zb+ny+nw/j/AHun7Wji+GqL/wBn4x/bO6uv5vq6v5X/AJur72hvtrZE1zszdSOdelfmh/G9nlGh2v8AzhF0m15u/tzLvDFctx3u9zfD4rv2z0g7x4emzhXZ+MLEp1bXsdp7TsfyX9OZZ32VdZpsNam5+LpD462v3e5hV6Ng3jeGx7wp3mV1ZWZ+GzrMzz0yrXf0FGszp1o0j1azKpZ3wWreHzTiRObZmyR7q8zx3axN9617xvO/jtspb+IrcMFuDb9yZQ5Ndnrl07OXm95bTpp5eGk4nH4QOKsQ4s3XxLnln02umbct+bkdzfdW+7nWt2jXLN3TRpuR6VNJNML2a40ey5l/HdmF9j8u+rzjh52K9q4+Pv2jM1cWb1c4y23e9Oe1Zl9PKmZ8vpb2fTRGyLwFuJn3dbs4fry2LKyrvO7K5X/Vd2/XQ/bZvTZaf//Z') 0 0 no-repeat;background-position: right 0 top 50%, 0 0;background-size: 5vw auto, 100%;}");
void Animation()
{
    if(reloadPage && loadNextPage)
    {
        animation = false;
    }
    else if(reloadPage && !loadNextPage)
    {
        animation = false;
    }
    else if(!reloadPage && loadNextPage)
    {
        animation = true;
    }
    else if(!reloadPage && !loadNextPage)
    {
        animation = true;
    }
}
String Message(String message)
{
    String _message;
    if(breakAction && reloadPage && !loadNextPage)
    {
        Alert Alert_NoExecute(message);
        _message = Alert_NoExecute.get();
    }
    Animation();
    return _message;
}

String Page_Contacts()
{
    ContextHeader ContHead("Обратная связь");
    ReferenceInFrame RefSupport("Телефон службы поддержки клиентов", "tel:", "+7 (977) 613-36-11");
    String controllerSN = "";
    ByteArrayToHexString(controllerSN, "", controllerSerialNumber, 6);
    ReferenceInFrame RefSaleEmail("E-mail технического отдела", "mailto:", "amalgama2002@mail.ru", "Заводская настройка изделия № " + controllerSN, "Добрый день!");
    String href = "";
    if(mode == MODE_USER)
    {
        href = "MAIN_MENU";
    }
    else
    {
        href = "SERIAL_NUMBER";
    }
    Button Back("right", href, "FORM", "ButtonSubmit", "НАЗАД");
    String twoCol = buttonCap + Back.get();
    TwoCol TwoCol(twoCol);
    Form Form("FORM", TwoCol.get());
    String body = ContHead.get() + RefSupport.get() + RefSaleEmail.get() + Form.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Loading()
{
    int timeLeft = 10;
    String body = "<tr><td colspan=\"2\" style=\"height:100%\"><h4 id=\"blink\" style=\"font-size:10vw;text-align:center\">ЗАГРУЗКА</h4></td></tr><script>window.setTimeout(ChangeBlink, " + String((timeLeft * 1100), DEC) + ");function ChangeBlink(){document.getElementById('blink').innerHTML = \"Обновите страницу!\";}</script>";
    Html Html_Main(header, body, timeLeft, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_SerialNumber()
{
    String subHeader = "";
    if(mode == MODE_FACTORY)
    {
        subHeader = ("Заводские настройки");
    }
    else
    {
        subHeader = ("Инсталляционные настройки");
    }
    ContextHeader ContextHeader_Main(subHeader);
    String controllerSN = "";
    ByteArrayToHexString(controllerSN, "", controllerSerialNumber, 6);
    StatusInFrame StatusInFrame_SerialESP("Серийный номер контроллера", controllerSN);

    /* String deviceSN;
    if(deviceSerialNumber == "")
    {
        LineInputField LineInputField_SerialDevice("Серийный номер изделия", "DEVICE_SN", "FORM_NEXT", deviceSerialNumber, "text", true, "[A-Z0-9]{12,}", "this.value=this.value.replace(/[^A-Z0-9]+/g,'')", "12", "Device serial number", "Только заглавные латинские буквы + цифры. Длина строго 12 знаков.");
        deviceSN = LineInputField_SerialDevice.get();
    }
    else
    {
        StatusInFrame StatusInFrame_SerialDevice("Серийный номер изделия", deviceSerialNumber);
        deviceSN = StatusInFrame_SerialDevice.get();
    } */

    Text Text_1("ВНИМАНИЕ!!! Если в процессе настройки изделия произойдет отключение электропитания, процесс настройки сервопривода прийдется начать сначала!");
    TextContainer TextContainer_1(Text_1.get());
    Button Button_Contacts("left", "CONTACTS", "FORM_BACK", "ButtonSubmit", "КОНТАКТЫ");
    Form Form_Back("FORM_BACK", Button_Contacts.get());
    String href;
    if(mode == MODE_FACTORY)
    {
        href = "FACTORY_BUTTON";
    }
    else
    {
        href = "REST";
    }
    Button Button_FactorySettings("right", href, "FORM_NEXT", "ButtonSubmit", "НАСТРОЙКА");
    Form Form_Next("FORM_NEXT", Button_FactorySettings.get());
    TwoCol TwoCol_1(Form_Back.get() + Form_Next.get());
    String body = ContextHeader_Main.get() + StatusInFrame_SerialESP.get() + TextContainer_1.get() + TwoCol_1.get(); // + deviceSN
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_WirelessMode()
{
    ContextHeader ContextHeader_Main("Режим беспроводной сети");
    String defaultApId;
    String defaultApLable;
    if(mode == MODE_INSTALATION)
    {
        defaultApId = "CHANGE_DEFAULT_AP";
        defaultApLable = "ПРОПУСТИТЬ";
    }
    else
    {
        defaultApId = "OFF_WIRELESS";
        defaultApLable = "ВЫКЛЮЧИТЬ";
    }
    Button Button_DefaultAp("left", defaultApId, "FORM_MAIN", "ButtonSubmit", defaultApLable);
    Button Button_UserAp("right", "CHANGE_USER_AP", "FORM_MAIN", "ButtonSubmit", "ТОЧКА<BR>ДОСТУПА");
    TwoCol TwoCol1(Button_DefaultAp.get() + Button_UserAp.get());
    Button Button_WiFi("right", "CHANGE_WIFI", "FORM_MAIN", "ButtonSubmit", "WI-FI");
    String hreaf;
    if(mode == MODE_INSTALATION)
    {
        hreaf = "FAST_MO_SETUP";
    }
    else
    {
        hreaf = "SETTINGS";
    }
    Button Button_Back("left", hreaf, "FORM_MAIN", "ButtonSubmit", "НАЗАД");
    TwoCol TwoCol2(Button_Back.get() + Button_WiFi.get());
    Form Form("FORM_MAIN", TwoCol1.get() + TwoCol2.get());
    String body = ContextHeader_Main.get() + Form.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_UserAp()
{
    ContextHeader ContHead("Параметры точки доступа");
    
    LineInputField ApSsid("Название точки доступа", "AP_SSID", "FORM_AP", apSsid, "text", true, "[A-Za-z0-9]{1,}", "this.value=this.value.replace(/[^A-Za-z0-9]+/g,'')", "24", "SSID", "Не допускаются: длина менее 1-го символа, буквы отличные от латинских, спецсимволы и пробелы.");
    
    String pattern;
    if(apPassword.length() < 64)
    {
        pattern = "[A-Za-z0-9]{8,}";
    }
    else
    {
        pattern = "[A-Fa-f0-9]{64,}";
    }
    LineInputField ApPassword("Пароль", "AP_PASSWORD", "FORM_AP", apPassword, "password", true, pattern, "this.value=this.value.replace(/[^A-Za-z0-9]+/g,'')", "64", "WPA2 8~63 ASCII или 64 HEX", "От 8 до 63 символов из таблицы ASCII (A-Z,a-z,0-9) или 64 символа в формате HEX (A-F,a-f,0-9).");
    ApPassword.setEncrypt("function ChangeSize(){var input = document.getElementById(\"AP_PASSWORD\");var inputValue = document.getElementById(\"AP_PASSWORD\").value;if(inputValue.length == 64){input.setAttribute(\"pattern\", \"[A-Fa-f0-9]{64,}\");}else{input.setAttribute(\"pattern\", \"[A-Za-z0-9]{8,}\");}}");
    
    Select Select_Channel("FORM_AP","CHANNEL", "CHANNEL", "Канал связи");
    bool chAuto = false;
    bool ch1 = false;
    bool ch2 = false;
    bool ch3 = false;
    bool ch4 = false;
    bool ch5 = false;
    bool ch6 = false;
    bool ch7 = false;
    bool ch8 = false;
    bool ch9 = false;
    bool ch10 = false;
    bool ch11 = false;
    bool ch12 = false;
    bool ch13 = false;
    switch(apChannel)
    {
        case 0:
            chAuto = true;
            break;
        case 1:
            ch1 = true;
            break;
        case 2:
            ch2 = true;
            break;
        case 3:
            ch3 = true;
            break;
        case 4:
            ch4 = true;
            break;
        case 5:
            ch5 = true;
            break;
        case 6:
            ch6 = true;
            break;
        case 7:
            ch7 = true;
            break;
        case 8:
            ch8 = true;
            break;
        case 9:
            ch9 = true;
            break;
        case 10:
            ch10 = true;
            break;
        case 11:
            ch11 = true;
            break;
        case 12:
            ch12 = true;
            break;
        case 13:
            ch13 = true;
            break;
    }
    Select_Channel.setOption("auto", "Channel: Auto", chAuto);
    Select_Channel.setOption("1", "Channel: 1", ch1);
    Select_Channel.setOption("2", "Channel: 2", ch2);
    Select_Channel.setOption("3", "Channel: 3", ch3);
    Select_Channel.setOption("4", "Channel: 4", ch4);
    Select_Channel.setOption("5", "Channel: 5", ch5);
    Select_Channel.setOption("6", "Channel: 6", ch6);
    Select_Channel.setOption("7", "Channel: 7", ch7);
    Select_Channel.setOption("8", "Channel: 8", ch8);
    Select_Channel.setOption("9", "Channel: 9", ch9);
    Select_Channel.setOption("10", "Channel: 10", ch10);
    Select_Channel.setOption("11", "Channel: 11", ch11);
    Select_Channel.setOption("12", "Channel: 12", ch12);
    Select_Channel.setOption("13", "Channel: 13", ch13);
    
    String attachAuto = Select_Channel.getSetAttribute("value", "auto");
    Select_Channel.setOptionScript("auto", attachAuto);

    String attach1 = Select_Channel.getSetAttribute("value", "1");
    Select_Channel.setOptionScript("1", attach1);
    
    String attach2 = Select_Channel.getSetAttribute("value", "2");
    Select_Channel.setOptionScript("2", attach2);
    
    String attach3 = Select_Channel.getSetAttribute("value", "3");
    Select_Channel.setOptionScript("3", attach3);
    
    String attach4 = Select_Channel.getSetAttribute("value", "4");
    Select_Channel.setOptionScript("4", attach4);
    
    String attach5 = Select_Channel.getSetAttribute("value", "5");
    Select_Channel.setOptionScript("5", attach5);
    
    String attach6 = Select_Channel.getSetAttribute("value", "6");
    Select_Channel.setOptionScript("6", attach6);
    
    String attach7 = Select_Channel.getSetAttribute("value", "7");
    Select_Channel.setOptionScript("7", attach7);
    
    String attach8 = Select_Channel.getSetAttribute("value", "8");
    Select_Channel.setOptionScript("8", attach8);
    
    String attach9 = Select_Channel.getSetAttribute("value", "9");
    Select_Channel.setOptionScript("9", attach9);
    
    String attach10 = Select_Channel.getSetAttribute("value", "10");
    Select_Channel.setOptionScript("10", attach10);
    
    String attach11 = Select_Channel.getSetAttribute("value", "11");
    Select_Channel.setOptionScript("11", attach11);
    
    String attach12 = Select_Channel.getSetAttribute("value", "12");
    Select_Channel.setOptionScript("12", attach12);
    
    String attach13 = Select_Channel.getSetAttribute("value", "13");
    Select_Channel.setOptionScript("13", attach13);
    
    Checkbox HideAp("HIDE_AP", "FORM_AP", apHiddenSsid, "Скрыть сеть");
    CheckRadioContainer CheckboxContainer_HideAp("Отображение SSID", HideAp.get() + "<script>function ChangeRequiredHIDE_AP(){}</script>");

    String mac = "";
    ByteArrayToHexString(mac, ":", apMac, 6);
    if(mac == "00:00:00:00:00:00")
    {
        mac = "";
        char hiBytes[5];
        char lowBytes[9];
        snprintf(hiBytes, 5, "%04X", (uint16_t)(ESP.getEfuseMac() >> 32));
        for (int i = 0; i < strlen(hiBytes); i++)
        {
            mac += hiBytes[i];
        }
        snprintf(lowBytes, 9, "%08X", (uint32_t)(ESP.getEfuseMac()));
        for (int i = 0; i < strlen(lowBytes); i++)
        {
            mac += lowBytes[i];
        }
        ReturnSeparators(mac, 2, ":");
    }
    LineInputField ApMac("MAC адрес", "AP_MAC", "FORM_AP", mac, "text", true, "([0-9a-fA-F]{2}([:-]|$)){6}$|([0-9a-fA-F]{4}([.]|$)){3}", "", "17", "A0:B1:C2:D3:E4:F5", "12 знаков в формате HEX через двоеточие.");
    
    String ip = "";
    ByteArrayToDecString(ip, ".", apIp, 4);
    if(ip == "0.0.0.0")
    {
        ip = "";
    }
    LineInputField LineInputField_ApIp("IP адрес", "AP_IP", "FORM_AP", ip, "text", apStaticNetworkConfig, "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)", "", "15", "0.0.0.0", "IP Address");
    
    String mask = "";
    ByteArrayToDecString(mask, ".", apMask, 4);
    if(mask == "0.0.0.0")
    {
        mask = "";
    }
    LineInputField LineInputField_ApMask("Маска подсети", "AP_MASK", "FORM_AP", mask, "text", apStaticNetworkConfig, "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)", "", "15", "0.0.0.0", "IP Address");

    ShowHideBlock ShowHideBlock_NetworkSettings(LineInputField_ApIp.get() + LineInputField_ApMask.get(), "BLOCK_NETWORK_SETTINGS", !apStaticNetworkConfig);
    Checkbox Checkbox_ExtraOptions("ExtraOptions", "FORM_AP", apStaticNetworkConfig, "Сетевые настройки");
    String inputId[] = {"AP_IP", "AP_MASK"};
    Checkbox_ExtraOptions.setRequiredFalse(inputId, 2);
    CheckRadioContainer CheckRadioContainer_ExtraOptions("Дополнительные параметры", Checkbox_ExtraOptions.get());
    ShowHideBlock ShowHideBlock_Checbox(CheckRadioContainer_ExtraOptions.get(), "BLOCK_NETWORK_SETTINGS", Checkbox_ExtraOptions, true);

    Button Save("right", "SAVE_AP", "FORM_AP", "ButtonSubmit", "ПРИМЕНИТЬ");
    Button Back("left", "WIRELESS_MODE", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Ap("FORM_AP", Save.get());
    Form Form_Back("FORM_BACK", Back.get());
    TwoCol TwoCol(Form_Back.get() + Form_Ap.get());

    String body = ContHead.get() + ApSsid.get() + ApPassword.get() + Select_Channel.get() + CheckboxContainer_HideAp.get() + ApMac.get() + CheckRadioContainer_ExtraOptions.get() + ShowHideBlock_NetworkSettings.get() + ShowHideBlock_Checbox.get() + TwoCol.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssSelect.get() + CssPassword.get() + CssAnimation.get());
    return Html_Main.get();
}
String Page_WiFi()
{
    ContextHeader ContHead("Параметры Wi-Fi");
    LineInputField StaSsid("Название беспроводной сети", "STA_SSID", "FORM_STA", staSsid, "text", true, "[A-Za-z0-9]{1,}", "this.value=this.value.replace(/[^A-Za-z0-9]+/g,'')", "24", "SSID", "Только латинские буквы + цифры. Длина имени не может быть более 24 знаков.");

    Select EncryptedType("FORM_STA","ENCRYPT_TYPE", "STA_PASSWORD", "Тип шифрования");
    bool encOpen = false;
    bool encWep64 = false;
    bool encWep128 = false;
    bool encWpa = false;
    bool encWpa2 = false;
    bool encWpaWpa2 = false;
    switch(staEncryptionType)
    {
        case ENCRYPT_WEP64:
            encWep64 = true;
            break;
        case ENCRYPT_WEP128:
            encWep128 = true;
            break;
        case ENCRYPT_WPA:
            encWpa = true;
            break;
        case ENCRYPT_WPA2:
            encWpa2 = true;
            break;
        case ENCRYPT_WPA_WPA2:
            encWpaWpa2 = true;
            break;
        default:
            encOpen = true;
            break;
    }
    EncryptedType.setOption("OPEN", "Открытая сеть", encOpen);
    EncryptedType.setOption("WEP64", "WEP 64 bit", encWep64);
    EncryptedType.setOption("WEP128", "WEP 128 bit", encWep128);
    EncryptedType.setOption("WPA", "WPA", encWpa);
    EncryptedType.setOption("WPA2", "WPA2", encWpa2);
    EncryptedType.setOption("WPA_WPA2", "WPA/WPA2", encWpaWpa2);
    
    String attachOpen = EncryptedType.getSetAttribute("row", "hidden", "hidden") + EncryptedType.getRemoveAttribute("required");
    EncryptedType.setOptionScript("OPEN", attachOpen);

    String attachWep64 = EncryptedType.getRemoveAttribute("hidden") + EncryptedType.getSetAttribute("required", "required") + EncryptedType.getSetAttribute("maxlength", "10") + EncryptedType.getSetAttribute("pattern", "[A-Za-z0-9]{5,}") + EncryptedType.getSetAttribute("placeholder", "5 ASCII или 10 HEX") + EncryptedType.getSetAttribute("title", "5 символов из таблицы ASCII (A-Z,a-z,0-9) или 10 символов в формате HEX (A-F,a-f,0-9)");
    EncryptedType.setOptionScript("WEP64", attachWep64);

    String attachWep128 = EncryptedType.getRemoveAttribute("hidden") + EncryptedType.getSetAttribute("required", "required") + EncryptedType.getSetAttribute("maxlength", "26") + EncryptedType.getSetAttribute("pattern", "[A-Za-z0-9]{13,}") + EncryptedType.getSetAttribute("placeholder", "13 ASCII или 26 HEX") + EncryptedType.getSetAttribute("title", "13 символов из таблицы ASCII (A-Z,a-z,0-9) или 26 символов в формате HEX (A-F,a-f,0-9)");
    EncryptedType.setOptionScript("WEP128", attachWep128);

    String attachWpa = EncryptedType.getRemoveAttribute("hidden") + EncryptedType.getSetAttribute("required", "required") + EncryptedType.getSetAttribute("maxlength", "64") + EncryptedType.getSetAttribute("pattern", "[A-Za-z0-9]{8,}") + EncryptedType.getSetAttribute("placeholder", "8~63 ASCII или 64 HEX") + EncryptedType.getSetAttribute("title", "От 8 до 63 символов из таблицы ASCII (A-Z,a-z,0-9) или 64 символа в формате HEX (A-F,a-f,0-9)");
    EncryptedType.setOptionScript("WPA", attachWpa);

    String attachWpa2 = EncryptedType.getRemoveAttribute("hidden") + EncryptedType.getSetAttribute("required", "required") + EncryptedType.getSetAttribute("maxlength", "64") + EncryptedType.getSetAttribute("pattern", "[A-Za-z0-9]{8,}") + EncryptedType.getSetAttribute("placeholder", "8~63 ASCII или 64 HEX") + EncryptedType.getSetAttribute("title", "От 8 до 63 символов из таблицы ASCII (A-Z,a-z,0-9) или 64 символа в формате HEX (A-F,a-f,0-9)");
    EncryptedType.setOptionScript("WPA2", attachWpa2);

    String attachWpaWpa2 = EncryptedType.getRemoveAttribute("hidden") + EncryptedType.getSetAttribute("required", "required") + EncryptedType.getSetAttribute("maxlength", "64") + EncryptedType.getSetAttribute("pattern", "[A-Za-z0-9]{8,}") + EncryptedType.getSetAttribute("placeholder", "8~63 ASCII или 64 HEX") + EncryptedType.getSetAttribute("title", "От 8 до 63 символов из таблицы ASCII (A-Z,a-z,0-9) или 64 символа в формате HEX (A-F,a-f,0-9)");
    EncryptedType.setOptionScript("WPA_WPA2", attachWpaWpa2);

    LineInputField StaPassword("Пароль", "STA_PASSWORD", "FORM_STA", staPassword, "password", false);
    StaPassword.setEncrypt("function ChangeSize(){var input = document.getElementById(\"STA_PASSWORD\");var inputValue = document.getElementById(\"STA_PASSWORD\").value;var select = document.getElementById(\"ENCRYPT_TYPE\");var selectValue = select.options[select.selectedIndex].value;if(selectValue == \"WEP64\"){if(inputValue.length <= 5){input.setAttribute(\"pattern\", \"[A-Za-z0-9]{5,}\");}else if(inputValue.length > 5){input.setAttribute(\"pattern\", \"[A-Fa-f0-9]{10,}\");}}else if(selectValue == \"WEP128\"){if(inputValue.length <= 13){input.setAttribute(\"pattern\", \"[A-Za-z0-9]{13,}\");}else if(inputValue.length > 13){input.setAttribute(\"pattern\", \"[A-Fa-f0-9]{26,}\");}}else{if(inputValue.length == 64){input.setAttribute(\"pattern\", \"[A-Fa-f0-9]{64,}\");}else{input.setAttribute(\"pattern\", \"[A-Za-z0-9]{8,}\");}}}");
    
    String mac = "";
    ByteArrayToHexString(mac, ":", staMac, 6);
    if(mac == "00:00:00:00:00:00")
    {
        mac = "";
        char hiBytes[5];
        char lowBytes[9];
        snprintf(hiBytes, 5, "%04X", (uint16_t)(ESP.getEfuseMac() >> 32));
        for (int i = 0; i < strlen(hiBytes); i++)
        {
            mac += hiBytes[i];
        }
        snprintf(lowBytes, 9, "%08X", (uint32_t)(ESP.getEfuseMac()));
        for (int i = 0; i < strlen(lowBytes); i++)
        {
            mac += lowBytes[i];
        }
        ReturnSeparators(mac, 2, ":");
    }
    LineInputField StaMac("MAC адрес", "STA_MAC", "FORM_STA", mac, "text", true, "([0-9a-fA-F]{2}([:-]|$)){6}$|([0-9a-fA-F]{4}([.]|$)){3}", "", "17", "A0:B1:C2:D3:E4:F5", "12 знаков в формате HEX через двоеточие.");
    
    String ip = "";
    ByteArrayToDecString(ip, ".", staIp, 4);
    if(ip == "0.0.0.0")
    {
        ip = "";
    }
    LineInputField LineInputField_StaIp("IP адрес", "STA_IP", "FORM_STA", ip, "text", staStaticNetworkConfig, "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)", "", "15", "0.0.0.0", "IP Address");
    String mask = "";
    ByteArrayToDecString(mask, ".", staMask, 4);
    if(mask == "0.0.0.0")
    {
        mask = "";
    }
    LineInputField LineInputField_StaMask("Маска подсети", "STA_MASK", "FORM_STA", mask, "text", staStaticNetworkConfig, "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)", "", "15", "0.0.0.0", "IP Address");
    String gateway = "";
    ByteArrayToDecString(gateway, ".", staGateway, 4);
    if(gateway == "0.0.0.0")
    {
        gateway = "";
    }
    LineInputField LineInputField_StaGateway("Основной шлюз", "STA_GATEWAY", "FORM_STA", gateway, "text", staStaticNetworkConfig, "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)", "", "15", "0.0.0.0", "IP Address");

    ShowHideBlock ShowHideBlock_NetworkSettings(LineInputField_StaIp.get() + LineInputField_StaMask.get() + LineInputField_StaGateway.get(), "BLOCK_NETWORK_SETTINGS", !staStaticNetworkConfig);
    Checkbox Checkbox_ExtraOptions("ExtraOptions", "FORM_STA", staStaticNetworkConfig, "Сетевые настройки");
    String inputId[] = {"STA_IP", "STA_MASK", "STA_GATEWAY"};
    Checkbox_ExtraOptions.setRequiredFalse(inputId, 3);
    CheckRadioContainer CheckRadioContainer_ExtraOptions("Дополнительные параметры", Checkbox_ExtraOptions.get());
    ShowHideBlock ShowHideBlock_Checbox(CheckRadioContainer_ExtraOptions.get(), "BLOCK_NETWORK_SETTINGS", Checkbox_ExtraOptions, true);

    Button Back("left", "WIRELESS_MODE", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Button Save("right", "SAVE_STA", "FORM_STA", "ButtonSubmit", "ПРИМЕНИТЬ");
    Form Form1("FORM_STA", Save.get());
    Form Form2("FORM_BACK", Back.get());
    TwoCol TwoCol(Form2.get() + Form1.get());

    String body = ContHead.get() + StaSsid.get() + EncryptedType.get() + StaPassword.get() + StaMac.get() + CheckRadioContainer_ExtraOptions.get() + ShowHideBlock_NetworkSettings.get() + ShowHideBlock_Checbox.get() + TwoCol.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssSelect.get() + CssPassword.get() + CssAnimation.get());
    return Html_Main.get();
}

String Page_Factory_TestFactoryButton()
{
    ContextHeader ContextHeader_Main("Тест заводской кнопки");
    String result = "Выполните тест";
    if(testFactoryButton)
    {
        result = "ТЕСТ ПРОЙДЕН";
    }
    if(event == EVENT_BUTTON_FACTORY_TEST)
    {
        result = "<div style=\"font-size:10vw;padding-right:6vw;text-align:center\" id=\"countdown\"></div><script>let timer;let x = " + String(testDuration / 1000, DEC) + ";countdown();function countdown(){document.getElementById('countdown').innerHTML = x;x--;if(x < 0){clearTimeout(timer);}else{timer = setTimeout(countdown, 1000);}}</script>";
    }
    StatusInFrame StatusInFrame_Result("Результат тестирования", result);

    Button Button_Help("left", "HELP_FACTORY_BUTTON", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Help("FORM_HELP", Button_Help.get());
    String buttonTestMode;
    String buttonTestLable;
    float calcRefresh;
    if(event == EVENT_BUTTON_FACTORY_TEST)
    {
        buttonTestMode = "ButtonCounterAction";
        buttonTestLable = "ПРЕРВАТЬ<BR>ТЕСТ";
        calcRefresh = testDuration / 1000;
    }
    else
    {
        buttonTestMode = "ButtonAction";
        buttonTestLable = "ТЕСТ";
        calcRefresh = 0;
    }
    Button Button_Test("right", "TEST_FACTORY_BUTTON", "FORM_TEST", buttonTestMode, buttonTestLable);
    Button_Test.setWindowScroll();
    Form Form_Test("FORM_TEST", Button_Test.get());
    TwoCol TwoCol_1(Form_Help.get() + Form_Test.get());

    Button Button_Back("left", "SERIAL_NUMBER", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "FACTORY_SERVO", "FORM_NEXT", "ButtonSubmit", "ДАЛЕЕ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_NEXT", Button_Next.get());
    TwoCol TwoCol_2(Form_Back.get() + Form_Next.get());

    String body = Message("Тест кнопки сброса заводских настроек не завершен!") + ContextHeader_Main.get() + StatusInFrame_Result.get() + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, calcRefresh, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_Factory_TestFactoryButtonHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("Для проведения теста кнопки сброса заводских настроек необходимо подать напряжение 3.3V на " + String(BUTTON_FACTORY_IN, DEC) + " пин контроллера.");
    Text Text_2("Далее нажмите на кнопку ТЕСТ и дождитесь результата проверки, которая займет " + String((TIME_LONG_HOLD / 2) / 1000, DEC) + " секунд.");
    Text Text_3("ПРЕДУПРЕЖДЕНИЕ: не превышайте напряжение 3.3V, это может вывести контроллер из строя!");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get());
    Button Button_Back("right", "FACTORY_BUTTON", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Factory_TestServo()
{
    ContextHeader ContextHeader_Main("Тест сервопривода");

    String freq = "";
    if(frequency != 0)
    {
        freq = frequency;
    }
    LineInputField LineInputField_Frequency("Частота управляющего сигнала", "FREQUENCY", "FORM_TEST", freq, "text", true, "[0-9]{,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "", "Гц", "Частота в герцах");
    
    String angle = "";
    if(rotateAngle != 0)
    {
        angle = rotateAngle;
    }
    LineInputField LineInputField_Angle("Угол поворота сервопривода", "ANGLE", "FORM_TEST", angle, "text", true, "[0-9]{3,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "3", "180&deg - 360&deg", "Только числа.");
        
    String minPulse = "";
    if(minPulseWidth != 0)
    {
        minPulse = minPulseWidth;
    }
    LineInputField LineInputField_MinPulse("Длительность минимального импульса", "MIN_PULSE", "FORM_TEST", minPulse, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "5", "мс", "Миллисекунды");

    String maxPulse = "";
    if(maxPulseWidth != 0)
    {
        maxPulse = maxPulseWidth;
    }
    LineInputField LineInputField_MaxPulse("Длительность максимального импульса", "MAX_PULSE", "FORM_TEST", maxPulse, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "5", "мс", "Миллисекунды");

    LineInputField LineInputField_DelayPulse("Задержка между поворотом на 1 градус", "DELAY_PULSE", "FORM_TEST", String(delayPulse, DEC), "text", true, "[0-9]{,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "2", "мс", "Миллисекунды");
    LineInputField LineInputField_DelayBetween("Пауза перед сменой направления", "DELAY_BETWEEN", "FORM_TEST", String(delayBetween, DEC), "text", true, "[0-9]{,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "4", "мс", "Миллисекунды");

    ShowHideBlock ShowHideBlock_Delay(LineInputField_DelayPulse.get() + LineInputField_DelayBetween.get(), "BLOCK_DELAY", true);
    Checkbox Checkbox_ExtraOptions("ExtraOptions", "CHECKBOX_HIDE", false, "Скорость вращения");
    CheckRadioContainer CheckRadioContainer_ExtraOptions("Дополнительные параметры",Checkbox_ExtraOptions.get());
    ShowHideBlock ShowHideBlock_Checbox(CheckRadioContainer_ExtraOptions.get(), "BLOCK_DELAY", Checkbox_ExtraOptions, true);

    Button Button_Help("left", "HELP_SERVO", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Help("FORM_HELP", Button_Help.get());
    String buttonTestMode;
    String buttonTestLable;
    float calcRefresh;
    if(event == EVENT_SERVO_TEST)
    {
        buttonTestMode = "ButtonCounterAction";
        buttonTestLable = "ПРЕРВАТЬ<BR>ТЕСТ";
        calcRefresh = delayBetween + 2 * rotateAngle * delayPulse;
        calcRefresh = ceil(calcRefresh / 1000);
    }
    else
    {
        buttonTestMode = "ButtonAction";
        buttonTestLable = "ТЕСТ";
        calcRefresh = 0;
    }
    Button Button_Test("right", "TEST_SERVO", "FORM_TEST", buttonTestMode, buttonTestLable);
    Button_Test.setWindowScroll();
    Form Form_Test("FORM_TEST", Button_Test.get());
    TwoCol TwoCol_1(Form_Help.get() + Form_Test.get());

    Button Button_Back("left", "FACTORY_BUTTON", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "CALIBRATE_SERVO", "FORM_NEXT", "ButtonSubmit", "ДАЛЕЕ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_NEXT", Button_Next.get());
    TwoCol TwoCol_2(Form_Back.get() + Form_Next.get());

    String body = Message("Тест сервопривода не завершен!") + ContextHeader_Main.get() + LineInputField_Frequency.get() + LineInputField_Angle.get() + LineInputField_MinPulse.get() + LineInputField_MaxPulse.get() + CheckRadioContainer_ExtraOptions.get() + ShowHideBlock_Delay.get() + ShowHideBlock_Checbox.get() + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, calcRefresh, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_Factory_TestServoHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    TextHeader TextHeader_Main("Параметры рекомендуемых сервоприводов:");
    TextContainer TextContainer_TextHeader_Main(TextHeader_Main.get());
    List CoronaDS329MG("CORONA_DS329MG", "Corona DS-329MG");
    ListContainer List_Servo(CoronaDS329MG.get());
    Button Back("left", "FACTORY_SERVO", "FORM", "ButtonSubmit", "НАЗАД");
    TwoCol TwoCol_1(Back.get() + buttonCap);
    Form Form("FORM", TwoCol_1.get());
    String body = ContextHeader_Main.get() + TextContainer_TextHeader_Main.get() + List_Servo.get() + Form.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Factory_Reference_CoronaDS329MG()
{
    ContextHeader ContextHeader_Main("Справка");
    TextHeader TextHeader_Main("Corona DS-329MG");
    TextContainer TextContainer_TextHeader_Main(TextHeader_Main.get());
    Table Table_Main;
    Table_Main.set("Параметр<td>Значение");
    Table_Main.set("Частота управляющего сигнала<td>20Гц");
    Table_Main.set("Максимальный угол<td>180&deg");
    Table_Main.set("Минимальная длительность импульса<td>620мс");
    Table_Main.set("Максимальная длительность импульса<td>2500мс");
    
    Button Back("right", "HELP_SERVO", "FORM", "ButtonSubmit", "НАЗАД");
    TwoCol TwoCol_1(buttonCap + Back.get());
    Form Form("FORM", TwoCol_1.get());
    String body = ContextHeader_Main.get() + TextContainer_TextHeader_Main.get() + Table_Main.get() + Form.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Factory_CalibrateServo()
{
    ContextHeader ContextHeader_Main("Калибровка сервопривода");

    String message = "Выполните калибровку трех положений рычага сервопривода";
    String calibrateValues = "";
    if(SERVO_MAIN.getMinAnalog() && SERVO_MAIN.getMidAnalog() && SERVO_MAIN.getMaxAnalog() && !sortBeforeCalibServ)
    {
        short temp;
        short arrAnalogSig[] = {SERVO_MAIN.getMinAnalogSig(), SERVO_MAIN.getMidAnalogSig(), SERVO_MAIN.getMaxAnalogSig()};
        for(short i = 0; i < 2; i++)
        {
            for(short j = 2; j > 0; j--)
            {
                if(arrAnalogSig[j] < arrAnalogSig[j - 1])
                {
                    temp = arrAnalogSig[j - 1];
                    arrAnalogSig[j - 1] = arrAnalogSig[j];
                    arrAnalogSig[j] = temp;
                }
            }
        }
        SERVO_MAIN.setMinAnalogSig(arrAnalogSig[0]);
        SERVO_MAIN.setMidAnalogSig(arrAnalogSig[1]);
        SERVO_MAIN.setMaxAnalogSig(arrAnalogSig[2]);
        sortBeforeCalibServ = true;
        calibrateValues += "Min: " + String(SERVO_MAIN.getMinAnalogSig(), DEC) + ", Mid: " + String(SERVO_MAIN.getMidAnalogSig(), DEC) + ", Max: " + String(SERVO_MAIN.getMaxAnalogSig(), DEC);
    }
    else if(!SERVO_MAIN.getMinAnalog() && !SERVO_MAIN.getMidAnalog() && !SERVO_MAIN.getMaxAnalog())
    {
        calibrateValues += "Замерьте положения рычага сервопривода на 3, 6 и 9 часов";
    }
    else if(SERVO_MAIN.getMinAnalog() && !SERVO_MAIN.getMidAnalog() && !SERVO_MAIN.getMaxAnalog())
    {
        calibrateValues += String(SERVO_MAIN.getMinAnalogSig(), DEC);
    }
    else if(SERVO_MAIN.getMinAnalog() && SERVO_MAIN.getMidAnalog() && !SERVO_MAIN.getMaxAnalog())
    {
        calibrateValues += String(SERVO_MAIN.getMidAnalogSig(), DEC);
    }
    else if(sortBeforeCalibServ)
    {
        calibrateValues += "Min: " + String(SERVO_MAIN.getMinAnalogSig(), DEC) + ", Mid: " + String(SERVO_MAIN.getMidAnalogSig(), DEC) + ", Max: " + String(SERVO_MAIN.getMaxAnalogSig(), DEC);
        message = "Калибровочный тест не пройден!";
    }
    
    StatusInFrame StatusInFrame_CalibrateValues("Результаты замера положений рычага", calibrateValues);

    Button Button_Reset("left", "RESET_CALIBRATE", "FORM", "ButtonSubmit", "СБРОС");
    Button_Reset.setWindowScroll();
    Form Form_Reset("FORM", Button_Reset.get());
    Button Button_Calibrate("right", "READ_ANALOG_SERVO", "FORM_CALIBRATE", "ButtonSubmit", "КАЛИБРОВКА");
    Button_Calibrate.setWindowScroll();
    Form Form_Calibrate("FORM_CALIBRATE", Button_Calibrate.get());
    TwoCol TwoCol_1(Form_Reset.get() + Form_Calibrate.get());

    short minDeg = SERVO_MAIN.getCalibMinAng();
    short midDeg = SERVO_MAIN.getCalibMidAng();
    short maxDeg = SERVO_MAIN.getCalibMaxAng();
    String calibrateDegrees = "";
    if(minDeg == DEFAULT_SHORT && midDeg == DEFAULT_SHORT && maxDeg == DEFAULT_SHORT)
    {
        calibrateDegrees += "Рабочий диаппазон";
    }
    else
    {
        calibrateDegrees += "Min: " + String(minDeg, DEC) + "&deg, Mid: " + String(midDeg, DEC) + "&deg, Max: " + String(maxDeg, DEC) + "&deg";
        //calibrateDegrees += String(SERVO_MAIN.getActualAngle(), DEC);
    }
    StatusInFrame StatusInFrame_CalibrateDegrees("Максимальный рабочий диаппазаон", calibrateDegrees);

    Button Button_Help("left", "HELP_CALIBRATE_SERVO", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Help("FORM_HELP", Button_Help.get());
    String buttonCalibrateMode;
    String buttonCalibrateLable;
    float calcRefresh;
    if(event == EVENT_SERVO_CALIBRATE_TEST)
    {
        buttonCalibrateMode = "ButtonCounterAction";
        buttonCalibrateLable = "ПРЕРВАТЬ<BR>ТЕСТ";
        calcRefresh = ceil(2);
    }
    else
    {
        buttonCalibrateMode = "ButtonAction";
        buttonCalibrateLable = "ТЕСТ";
        calcRefresh = 0;
    }
    Button Button_TestCalibrate("right", "TEST_CALIBRATE_SERVO", "FORM_CALIBRATE_SERVO", buttonCalibrateMode, buttonCalibrateLable);
    Button_TestCalibrate.setWindowScroll();
    Form Form_TestCalibrate("FORM_CALIBRATE_SERVO", Button_TestCalibrate.get());
    TwoCol TwoCol_2(Form_Help.get() + Form_TestCalibrate.get());

    Button Button_Back("left", "FACTORY_SERVO", "FORM", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM", Button_Back.get());
    Button Button_Next("right", "MAIN_BUTTON", "FORM_NEXT", "ButtonSubmit", "ДАЛЕЕ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_NEXT", Button_Next.get());
    TwoCol TwoCol_3(Form_Back.get() + Form_Next.get());

    String body = Message(message) + ContextHeader_Main.get() + StatusInFrame_CalibrateValues.get() + TwoCol_1.get() + StatusInFrame_CalibrateDegrees.get() + TwoCol_2.get() + TwoCol_3.get();
    Html Html_Main(header, body, calcRefresh, pageYOffset, animation, landscape);
    if(animation)
	{
		Html_Main.setCss(CssAnimation.get());
	}
	return Html_Main.get();
}
String Page_Factory_CalibrateServoHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("1. Выполните калибровку углов рычага сервопривода относительно его корпуса так, чтобы конец рычага поочередно указывал на 3, 6 и 9 часов на круглом циферблате настенных часов. ВНИМАНИЕ! Углы должны быть максимально прямыми(т.е. 90&deg). Последовательность измерений не важна. Если замер положения оказался неточным, можно сбросить все замеры и выполнить их заново.");
    Text Text_2("2. После того как в информационном окне появятся все три замеренных значения (min, mid и max), запустите тест калибровочных углов. Результаты замеренных значений представляют сопротивления потенциометра от 0 до 3.3V, преобразованные через 12 битный АЦП, т.е. от 0 до 4095 единиц на весь диаппазон вращения сервопривода.");
    Text Text_3("3. В момент выполнения теста внимательно наблюдайте за реальными углами остановки рычага сервопривода. Они должны быть кратны 90 градусам. Для более точного замера прямых углов может потребоваться запустить тест несколько раз, или выполнить калибровку повторно.");
    Text Text_4("4. После завершения тестирования калибровочных углов результаты появятся в соответствующем окне. Полученные углы могут значительно отличаться от прямых и несут вспомогательную функцию при наблюдении за реальными углами поворота.");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get() + Text_4.get());
    Button Button_Back("right", "CALIBRATE_SERVO", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
	return Html_Main.get();
}
String Page_Factory_TestMainButton()
{
    ContextHeader ContextHeader_Main("Тест пользовательской кнопки");
    String result = "Выполните тест";
    if(testMainButton)
    {
        result = "ТЕСТ ПРОЙДЕН";
    }
    if(event == EVENT_BUTTON_MAIN_TEST)
    {
        result = "<div style=\"font-size:10vw;padding-right:6vw;text-align:center\" id=\"countdown\"></div><script>let timer;let x = " + String(testDuration / 1000, DEC) + ";countdown();function countdown(){document.getElementById('countdown').innerHTML = x;x--;if(x < 0){clearTimeout(timer);}else{timer = setTimeout(countdown, 1000);}}</script>";
    }
    StatusInFrame StatusInFrame_Result("Результат тестирования", result);

    Button Button_Help("left", "HELP_MAIN_BUTTON", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Help("FORM_HELP", Button_Help.get());
    String buttonTestMode;
    String buttonTestLable;
    float calcRefresh;
    if(event == EVENT_BUTTON_MAIN_TEST)
    {
        buttonTestMode = "ButtonCounterAction";
        buttonTestLable = "ПРЕРВАТЬ<BR>ТЕСТ";
        calcRefresh = testDuration / 1000;
    }
    else
    {
        buttonTestMode = "ButtonAction";
        buttonTestLable = "ТЕСТ";
        calcRefresh = 0;
    }
    Button Button_Test("right", "TEST_MAIN_BUTTON", "FORM_TEST", buttonTestMode, buttonTestLable);
    Button_Test.setWindowScroll();
    Form Form_Test("FORM_TEST", Button_Test.get());
    TwoCol TwoCol_1(Form_Help.get() + Form_Test.get());

    Button Button_Back("left", "CALIBRATE_SERVO", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "MIC", "FORM_SAVE", "ButtonSubmit", "ДАЛЕЕ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_SAVE", Button_Next.get());
    TwoCol TwoCol_2(Form_Back.get() + Form_Next.get());

    /* String data = "<input type=\"hidden\" form=\"FORM_SAVE\" id=\"DAY\" name=\"DAY\" value=\"0\"><input type=\"hidden\" form=\"FORM_SAVE\" id=\"MONTH\" name=\"MONTH\" value=\"0\"><input type=\"hidden\" form=\"FORM_SAVE\" id=\"YEAR\" name=\"YEAR\" value=\"0\"><script>var date, day, month, year;date=new Date();day = date.getDate();month = date.getMonth() + 1;year = date.getFullYear();document.getElementById('DAY').value = day;document.getElementById('MONTH').value = month;document.getElementById('YEAR').value = year;</script>"; */

    String body = Message("Тест кнопки сброса пользовательских настроек не завершен!") + ContextHeader_Main.get() + StatusInFrame_Result.get() + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, calcRefresh, pageYOffset, animation, landscape);
    if(animation)
	{
		Html_Main.setCss(CssAnimation.get());
	}
	return Html_Main.get();
}
String Page_Factory_TestMainButtonHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("1. Нажмите и удерживайте пользовательскую кнопку.");
    Text Text_2("2. Далее нажмите на кнопку ТЕСТ и дождитесь результата проверки, которая займет " + String((TIME_LONG_HOLD / 2) / 1000, DEC) + " секунд.");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get());
    Button Button_Back("right", "MAIN_BUTTON", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
	return Html_Main.get();
}
String Page_Factory_TestMicrophone()
{
    ContextHeader ContextHeader_Main("Калибровка микрофона");
    String result = "Выполните замер тишины";
    if(quietAdc && quietDb == 0 && !loudAdc && loudDb == 0)
    {
        result = "Низ: " + String(MIC_MAIN.getQuiteBotAdc(), DEC) + ". Верх: " + String(MIC_MAIN.getQuiteTopAdc(), DEC) + ". Введите уровень тишины в децибелах";
    }
    else if(quietAdc && quietDb != 0 && !loudAdc && loudDb == 0)
    {
        result = "Уровень тишины: " + String(quietDb, DEC) + " DB. Выполните замер шума";
    }
    else if(quietAdc && quietDb != 0 && loudAdc && loudDb == 0)
    {
        result = "Низ: " + String(MIC_MAIN.getLoudBotAdc(), DEC) + ". Верх: " + String(MIC_MAIN.getLoudTopAdc(), DEC);
        if(MIC_MAIN.getLoudBotAdc() != 0 && MIC_MAIN.getLoudTopAdc() != 4095)
        {
            result += ". Увеличте громкость или сократите дистанцию от источника до микрофона";
        }
        else
        {
            result += ". Введите уровень шума в децибелах";
        }
    }
    else if(quietAdc && quietDb != 0 && loudAdc && loudDb != 0)
    {
        result = "Уровень шума " + String(loudDb, DEC) + " DB. Выполните тестовое измерение шума";
    }
    if(testMic)
    {
        result = "Текущий уровень шума: " + String(currentDb, DEC) + " DB";
    }
    if(event == EVENT_TEST_MIC)
    {
        result = "<div style=\"font-size:10vw;padding-right:6vw;text-align:center\" id=\"countdown\"></div><script>let timer;let x = " + String((TIME_HOLD / 2) / 1000, DEC) + ";countdown();function countdown(){document.getElementById('countdown').innerHTML = x;x--;if(x < 0){clearTimeout(timer);}else{timer = setTimeout(countdown, 1000);}}</script>";
    }
    StatusInFrame StatusInFrame_Result("Результат Настройки", result);

    Button Button_Reset("left", "RESET_MIC", "FORM_RESET", "ButtonCounterAction", "СБРОС");
    Button_Reset.setWindowScroll();
    Form Form_Reset("FORM_RESET", Button_Reset.get());
    String micTestMode;
    String micTestLable;
    float calcRefresh;
    if(event == EVENT_TEST_MIC)
    {
        micTestMode = "ButtonCounterAction";
        micTestLable = "ПРЕРВАТЬ<BR>ТЕСТ";
        calcRefresh = (TIME_HOLD / 2) / 1000;
    }
    else
    {
        micTestMode = "ButtonAction";
        micTestLable = "ТЕСТ";
        calcRefresh = 0;
    }
    Button Button_Test("right", "TEST_MIC", "FORM_TEST", micTestMode, micTestLable);
    Button_Test.setWindowScroll();
    Form Form_Test("FORM_TEST", Button_Test.get());
    TwoCol TwoCol_1(Form_Reset.get() + Form_Test.get());

    LineInputField LineInputField_Db("Уровень шума в децибелах", "DB", "FORM_ENTER", "", "text", true, "[0-9]{,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "", "Db", "Уровень шума в децибелах");
    String lineInputField_Db;
    if(quietAdc && quietDb == 0 && !loudAdc && loudDb == 0)
    {
        lineInputField_Db = LineInputField_Db.get();
    }
    else if(quietAdc && quietDb != 0 && loudAdc && loudDb == 0)
    {
        lineInputField_Db = LineInputField_Db.get();
    }
    else
    {
        lineInputField_Db = LineInputField_Db.getHide();
    }

    Button Button_Help("left", "HELP_MIC", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Help("FORM_HELP", Button_Help.get());
    Button Button_Enter("right", "ENTER_DB_MIC", "FORM_ENTER", "ButtonSubmit", "ВВОД");
    Button_Enter.setWindowScroll();
    Form Form_Enter("FORM_ENTER", Button_Enter.get());
    TwoCol TwoCol_2(Form_Help.get() + Form_Enter.get());


    Button Button_Back("left", "MAIN_BUTTON", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "SAVE_FACTORY_SETTINGS", "FORM_SAVE", "ButtonSubmit", "СОХРАНИТЬ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_SAVE", Button_Next.get());
    TwoCol TwoCol_3(Form_Back.get() + Form_Next.get());

    String data = "<input type=\"hidden\" form=\"FORM_SAVE\" id=\"DAY\" name=\"DAY\" value=\"0\"><input type=\"hidden\" form=\"FORM_SAVE\" id=\"MONTH\" name=\"MONTH\" value=\"0\"><input type=\"hidden\" form=\"FORM_SAVE\" id=\"YEAR\" name=\"YEAR\" value=\"0\"><script>var date, day, month, year;date=new Date();day = date.getDate();month = date.getMonth() + 1;year = date.getFullYear();document.getElementById('DAY').value = day;document.getElementById('MONTH').value = month;document.getElementById('YEAR').value = year;</script>";

    String body = Message("Настройка микрофона не выполнена!") + ContextHeader_Main.get() + StatusInFrame_Result.get() + TwoCol_1.get() + lineInputField_Db + TwoCol_2.get() + TwoCol_3.get() + data;
    Html Html_Main(header, body, calcRefresh, pageYOffset, animation, landscape);
    if(animation)
	{
		Html_Main.setCss(CssAnimation.get());
	}
	return Html_Main.get();
}
String Page_Factory_TestMicrophoneHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("Для замера уровня шума используйте специализированный прибор или приложение со смартфона, например \"Шумомер\". Для точной калибровки используйте стабильный источник шума. Тестируемый микрофоны и микрофон измерительного прибора должны быть направлены в одну сторону.");
    Text Text_2("1. Замерьте уровень тишины в помещении с помощью кнопки ТЕСТ.");
    Text Text_3("2. Введите уровень тишины в децибелах используя поле ввода и кнопку ВВОД.");
    Text Text_4("3. Замерьте уровень шума в помещении одновременно на обоих устройствах. Результат замера будет засчитан, если значение нижнего предела АЦП составит 0, а верхнего 4095. В противном случае увеличте громкость источника шума и повторите попытку.");
    Text Text_5("4. Введите полученный уровень шума в децибелах.");
    Text Text_6("5. Выполниет тестирование. При необходимости выполните сброс и повторите тестирование.");
    Text Text_7("ВНИМАНИЕ! После нажатия на кнопку СОХРАНИТЬ, контроллер перезагрузится в инсталляционный режим. Для изменения ранее выбранных параметров необходимо будет сбросить заводскихе настроеки.");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get() + Text_4.get() + Text_5.get() + Text_6.get() + Text_7.get());
    Button Button_Back("right", "MIC", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
	return Html_Main.get();
}

String Page_Installation_RestPosition()
{
    ContextHeader ContextHeader_Main("Положение покоя");
    String result = "Выполните замер";
    if(restCalibrate)
    {
        short startPositionModul = startPosition;
        if(startPosition < 0)
        {
            startPositionModul = startPosition * (-1);
        }
        if(startPositionModul == 0)
        {
            result = "Идеально! Отклонение 0&deg";
        }else if(startPositionModul > 0 && startPositionModul <= goodDeflection)
        {
            result = "Хорошо! Отклонение " + String(startPosition, DEC) + "&deg";
        }else if(startPositionModul > goodDeflection && startPositionModul <= badDeflection)
        {
            result = "Нормально! Отклонение " + String(startPosition, DEC) + "&deg";
        }else if(startPositionModul > badDeflection)
        {
            result = "Плохо! Отклонение " + String(startPosition, DEC) + "&deg, требуется регулировка положения изделия";
        }
    }
    StatusInFrame StatusInFrame_Result("Точность установки изделия в градусах", result);

    Button Button_Help("left", "HELP_REST", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Help("FORM_HELP", Button_Help.get());
    Button Button_Test("right", "TEST_REST", "FORM_TEST", "ButtonAction", "ЗАМЕР");
    Button_Test.setWindowScroll();
    Form Form_Test("FORM_TEST", Button_Test.get());
    TwoCol TwoCol_1(Form_Help.get() + Form_Test.get());

    Button Button_Back("left", "SERIAL_NUMBER", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "MODE_CALIBRATION", "FORM_NEXT", "ButtonSubmit", "ДАЛЕЕ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_NEXT", Button_Next.get());
    TwoCol TwoCol_2(Form_Back.get() + Form_Next.get());

    String body = Message("Отрегулируйте положение изделия и выполните ЗАМЕР!") + ContextHeader_Main.get() + StatusInFrame_Result.get() + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, 0, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_Installation_RestPositionHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("Перед началом настройки прочно зафиксируйте телескопический кранштейн изделия и соедините рычаг с валом и шарниром.");
    Text Text_2("Убедитесь что раскачивающаяся часть кроватки находится в состоянии покоя.");
    Text Text_3("Нажмите на кнопку \"ЗАМЕР\" для получения результата точности установки.");
    Text Text_4("Результат замера представлен в градусах, он показывает отклонение от калибровочного центра. Если угол отклонения превысит " + String(badDeflection, DEC) + "&deg, то необходимо отрегулировать положение изделия с помощью телескопических направляющих.");
    Text Text_5("С помощью знака (-) перед полученным результатом можно определить направление, в котором надо смещать изделие относительно неподвижной части кроватки.");
    Text Text_6("Чем точнее установка, тем больше амплитуда качения кроватки будет в результате!");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get() + Text_4.get() + Text_5.get() + Text_6.get());
    Button Button_Back("right", "REST", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Installation_SettingMode()
{
    ContextHeader ContextHeader_Main("Метод замера амплитуды");

    Button Button_Manual("left", "AMPLITUDE_MANUAL", "FORM_MAIN", "ButtonSubmit", "РУЧНАЯ<BR>НАСТРОЙКА");
    Button Button_Test("right", "AMPLITUDE_AUTO", "FORM_MAIN", "ButtonSubmit", "АВТО<BR>НАСТРОЙКА");
    TwoCol TwoCol_1(Button_Manual.get() + Button_Test.get());

    Button Button_Back("left", "REST", "FORM_MAIN", "ButtonSubmit", "НАЗАД");
    TwoCol TwoCol_2(Button_Back.get() + buttonCap);

    Form Form_Main("FORM_MAIN", TwoCol_1.get() + TwoCol_2.get());

    String body = ContextHeader_Main.get() + Form_Main.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Installation_SettingModeHelp()
{
    return "";
}
String Page_Installation_ManualCalibrateAmplitude()
{
    ContextHeader ContextHeader_Main("Ручной замер амплитуды");
    
    String buttonMeashureMode = "ButtonAction";
    String buttonMeashureLable = "ЗАМЕР<BR>АМПЛИТУДЫ";
    String result = "Выполните замер амплитуды";
    if(amplitudeMeashure)
    {
        result = "Замер амплитуды";
        buttonMeashureLable = "ПОДТВЕРДИТЬ<BR>ЗАМЕР";
    }
    else if(amplitudeMeashureComplite)
    {
        result = "Углы повотора от: " + String(extremeMinusAngle, DEC) + "&deg до: " + String(extremePlusAngle, DEC) + "&deg Максимальная амплитуда " + String(maxAmplitude, DEC) + "&deg";
        buttonMeashureMode = "ButtonCounterAction";
        buttonMeashureLable = "СБРОС";
    }

    StatusInFrame StatusInFrame_Result("Результат тестирования", result);

    Button Button_Help("left", "HELP_AMPLITUDE", "FORM_MAIN", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_MAIN", Button_Help.get());
    Button Button_Measure("right", "AMPLITUDE_MEASURE", "FORM_MEASURE", buttonMeashureMode, buttonMeashureLable);
    Button_Measure.setWindowScroll();
    Form Form_Measure("FORM_MEASURE", Button_Measure.get());
    TwoCol TwoCol_1(Form_Button_Help.get() + Form_Measure.get());

    Button Button_Back("left", "MODE_CALIBRATION", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "SLOW_MO_SETUP", "FORM_SAVE", "ButtonSubmit", "СОХРАНИТЬ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_SAVE", Button_Next.get());
    TwoCol TwoCol_2(Form_Back.get() + Form_Next.get());

    String body = Message("Не выполнен замер амплитуды") + ContextHeader_Main.get() + StatusInFrame_Result.get() + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, 0, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_Installation_ManualCalibrateAmplitudeHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("Запустите процедуру замера амплитуды качения с помощью кнопки \"ЗАМЕР АМПЛИТУДЫ\".");
    Text Text_2("Раскачивайте кроватку до максимальной возможной амплитуды. Выполните несколько раскачиваний на максимальной амплитуде для получения болле точных результатов.");
    Text Text_3("Нажмите на кнопку \"ПОДТВЕРДИТЬ ЗАМЕР\".");
    Text Text_4("Если во время замера что-то помешало раскачать кроватку до максимальной амплитуды можно выполнить \"СБРОС\" и повторить все операции заново.");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get() + Text_4.get());
    Button Button_Back("right", "AMPLITUDE_MANUAL", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Installation_ManualSlow()
{
    ContextHeader ContextHeader_Main("Настройка минимальной скорости");
    String status = "Заполните параметры и выполните тест";
    if(slowMoTest)
    {
        status = "Выполняется тестовый запуск";
    }
    if(slowMoTestComplite)
    {
        status = "Если тестирование успешно нажмите кнопку \"СОХРАНИТЬ\"";
    }
    if(SERVO_MAIN.checkGenerationError())
    {
        status = "Совокупность указанных параметров не позволяет построить кривую ускорения сервопривода!";
    }
    if(!descendingAccModel)
    {
        status = "Модель ускорения не соответствует требованиям!";
    }
    StatusInFrame StatusInFrame_Status("Состояние", status);
    String minD = "";
    minD = String(minDelaySlow, DEC);
    LineInputField LineInputField_MinDelay("Минимальная задержка поворота", "MIN_SLOW_DELAY", "FORM_TEST", minD, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "2", "по умолчанию: 6мс", "0 - 99");
    String maxD = "";
    maxD = String(maxDelaySlow, DEC);
    LineInputField LineInputField_MaxDelay("Максимальная задержка поворота", "MAX_SLOW_DELAY", "FORM_TEST", maxD, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "2", "по умолчанию: 20мс", "0 - 99");
    String betDelMin = "";
    betDelMin = String(betweenDelayMinSlow, DEC);
    LineInputField LineInputField_BetweenDelayMin("Задержка между сменой направления при минимальной амплитуде", "BET_SLOW_MIN_DELAY", "FORM_TEST", betDelMin, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "4", "по умолчанию: 150мс", "0 - 9999");
    String betDelMax = "";
    betDelMax = String(betweenDelayMaxSlow, DEC);
    LineInputField LineInputField_BetweenDelayMax("Задержка между сменой направления при максимальной амплитуде", "BET_SLOW_MAX_DELAY", "FORM_TEST", betDelMax, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "4", "по умолчанию: 100мс", "0 - 9999");
    String inc = "";
    inc = String(incrementSlow, DEC);
    LineInputField LineInputField_Increment("Увеличение угла раскачивания", "SLOW_INCREMENT", "FORM_TEST", inc, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "2", "по умолчанию: 3&deg", "0 - 90");
    String accModel = "";
    float sum = 0;
    for(byte i = 0; i < 5; i++)
    {
        sum += accelerationModelSlow[i];
    }
    if(sum != 0)
    {
        FloatArrayToDecString(accModel, " ", accelerationModelSlow, SIZE_SPLINE_ARRAY);
    }
    LineInputField LineInputField_AccelerationModel("Модель ускорения", "SLOW_ACCELERATION", "FORM_TEST", accModel, "text", true, "((([-+])?[.,]\b(\"d+)(?:[Ee]([+-])?(\"d+)?)?\b)|(?:([+-])?\b(\"d+)(?:[.,]?(\"d+))?(?:[Ee]([+-])?(\"d+)?)?\b)([ ]|$)){5}", "", "19", "по умолчанию: 9.0 3.0 2.0 1.5 1.0", "5 чисел через пробел от 9.0 до 1.0");

    Button Button_Help("left", "HELP_SLOW_MO_TEST", "FORM_MAIN", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_MAIN", Button_Help.get());

    String buttonTestLable;
    if(slowMoTest)
    {
        buttonTestLable = "ЗАВЕРШИТЬ<BR>ТЕСТ";
    }
    else
    {
        buttonTestLable = "ТЕСТ";
    }

    Button Button_Test("right", "SLOW_MO_TEST", "FORM_TEST", "ButtonAction", buttonTestLable);
    Button_Test.setWindowScroll();
    Form Form_Test("FORM_TEST", Button_Test.get());
    TwoCol TwoCol_1(Form_Button_Help.get() + Form_Test.get());

    Button Button_Back("left", "AMPLITUDE_MANUAL", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "FAST_MO_SETUP", "FORM_SAVE", "ButtonSubmit", "СОХРАНИТЬ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_SAVE", Button_Next.get());
    TwoCol TwoCol_2(Form_Back.get() + Form_Next.get());

    String body = Message("Выполните тест") + ContextHeader_Main.get() + StatusInFrame_Status.get() + LineInputField_MinDelay.get() + LineInputField_MaxDelay.get() + LineInputField_BetweenDelayMin.get() + LineInputField_BetweenDelayMax.get() + LineInputField_Increment.get() + LineInputField_AccelerationModel.get() + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, 0, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_Installation_ManualSlowHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("Для первого теста рекомендуется использовать стандартные параметры. Не рекомендуется использовать значения, сильно отличающиеся от стандартных. Не допускайте избыточной нагрузки на сервопривод во сремя тестирования. Если вы хотите вернуться к стандартным параметрам, просто очистите поле ввода, и прочитайте параметр по умолчанию.");
    Text Text_2("Параметры: минимальная задержка, максимальная задержка и задержка между сменой направления измеряются в милисекундах. Чем они меньше, тем быстрее качение. Минимальная задержка отвечает за ускорение, а максимальная за торможение.");
    Text Text_3("Увеличение угла раскачивания влияет на то, как быстро кроватка станет качаться с максимальной амплитудой. Но чем больше увеличение градусов за такт качения, тем сложнее сервоприводу справиться с нагрузкой, особенно если механизм качения кроватки слишком тугой или ребенок очень тяжелый. Рекомендуется использовать средний параметр прирощения угла, сохранив запас мощности сервопривода.");
    Text Text_4("Модель ускорения влияет на переход от максимальной к минимальной задержке поворота. Модель описывается 5 целими или дробными числами. Значения элементов модели уменьшаются слева направо. Модель не допускает использования одинаковых чисел подряд, например: 9.0 5.0 5.0 2.0 1.0 или 9.0 5.5 5.5 2.0 1.0. Если указанная модель не может быть реализована, информация об этом будет отображена в поле \"Состояние\". Всегда указывайте первым число 9 или 9.0, а последним 1 или 1.0.");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get() + Text_4.get());
    Button Button_Back("right", "SLOW_MO_SETUP", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Installation_ManualFast()
{
    ContextHeader ContextHeader_Main("Настройка максимальной скорости");
    String status = "Заполните параметры и выполните тест";
    if(fastMoTest)
    {
        status = "Выполняется тестовый запуск";
    }
    if(fastMoTestComplite)
    {
        status = "Если тестирование успешно нажмите кнопку \"СОХРАНИТЬ\"";
    }
    if(SERVO_MAIN.checkGenerationError())
    {
        status = "Совокупность указанных параметров не позволяет построить кривую ускорения сервопривода!";
    }
    if(!descendingAccModel)
    {
        status = "Модель ускорения не соответствует требованиям!";
    }
    StatusInFrame StatusInFrame_Status("Состояние", status);
    String minD = "";
    minD = String(minDelayFast, DEC);
    LineInputField LineInputField_MinDelay("Минимальная задержка поворота", "MIN_FAST_DELAY", "FORM_TEST", minD, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "2", "по умолчанию: 3мс", "0 - 99");
    String maxD = "";
    maxD = String(maxDelayFast, DEC);
    LineInputField LineInputField_MaxDelay("Максимальная задержка поворота", "MAX_FAST_DELAY", "FORM_TEST", maxD, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "2", "по умолчанию: 10мс", "0 - 99");
    String betDelMin = "";
    betDelMin = String(betweenDelayMinFast, DEC);
    LineInputField LineInputField_BetweenDelayMin("Задержка между сменой направления при минимальной амплитуде", "BET_FAST_MIN_DELAY", "FORM_TEST", betDelMin, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "4", "по умолчанию: 250мс", "0 - 9999");
    String betDelMax = "";
    betDelMax = String(betweenDelayMaxFast, DEC);
    LineInputField LineInputField_BetweenDelayMax("Задержка между сменой направления при максимальной амплитуде", "BET_FAST_MAN_DELAY", "FORM_TEST", betDelMax, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "4", "по умолчанию: 200мс", "0 - 9999");
    String inc = "";
    inc = String(incrementFast, DEC);
    LineInputField LineInputField_Increment("Увеличение угла раскачивания", "FAST_INCREMENT", "FORM_TEST", inc, "text", true, "[0-9]{1,}", "this.value=this.value.replace(/[^0-9]+/g,'')", "2", "по умолчанию: 5&deg", "0 - 90");
    String accModel = "";
    float sum = 0;
    for(byte i = 0; i < 5; i++)
    {
        sum += accelerationModelFast[i];
    }
    if(sum != 0)
    {
        FloatArrayToDecString(accModel, " ", accelerationModelFast, SIZE_SPLINE_ARRAY);
    }
    LineInputField LineInputField_AccelerationModel("Модель ускорения", "FAST_ACCELERATION", "FORM_TEST", accModel, "text", true, "((([-+])?[.,]\b(\"d+)(?:[Ee]([+-])?(\"d+)?)?\b)|(?:([+-])?\b(\"d+)(?:[.,]?(\"d+))?(?:[Ee]([+-])?(\"d+)?)?\b)([ ]|$)){5}", "", "19", "по умолчанию: 9.0 3.0 2.0 1.2 1.0", "5 чисел через пробел от 9.0 до 1.0");

    Button Button_Help("left", "HELP_FAST_MO_TEST", "FORM_MAIN", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_MAIN", Button_Help.get());

    String buttonTestLable;
    if(fastMoTest)
    {
        buttonTestLable = "ЗАВЕРШИТЬ<BR>ТЕСТ";
    }
    else
    {
        buttonTestLable = "ТЕСТ";
    }

    Button Button_Test("right", "FAST_MO_TEST", "FORM_TEST", "ButtonAction", buttonTestLable);
    Button_Test.setWindowScroll();
    Form Form_Test("FORM_TEST", Button_Test.get());
    TwoCol TwoCol_1(Form_Button_Help.get() + Form_Test.get());

    Button Button_Back("left", "SLOW_MO_SETUP", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "WIRELESS_MODE", "FORM_SAVE", "ButtonSubmit", "СОХРАНИТЬ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_SAVE", Button_Next.get());
    TwoCol TwoCol_2(Form_Back.get() + Form_Next.get());

    String body = Message("Выполните тест") + ContextHeader_Main.get() + StatusInFrame_Status.get() + LineInputField_MinDelay.get() + LineInputField_MaxDelay.get() + LineInputField_BetweenDelayMin.get() + LineInputField_BetweenDelayMax.get() + LineInputField_Increment.get() + LineInputField_AccelerationModel.get() + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, 0, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_Installation_ManualFastHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("Для первого теста рекомендуется использовать стандартные параметры. Не рекомендуется использовать значения, сильно отличающиеся от стандартных. Не допускайте избыточной нагрузки на сервопривод во сремя тестирования. Если вы хотите вернуться к стандартным параметрам, просто очистите поле ввода, и прочитайте параметр по умолчанию.");
    Text Text_2("Параметры: минимальная задержка, максимальная задержка и задержка между сменой направления измеряются в милисекундах. Чем они меньше, тем быстрее качение. Минимальная задержка отвечает за ускорение, а максимальная за торможение.");
    Text Text_3("Увеличение угла раскачивания влияет на то, как быстро кроватка станет качаться с максимальной амплитудой. Но чем больше увеличение градусов за такт качения, тем сложнее сервоприводу справиться с нагрузкой, особенно если механизм качения кроватки слишком тугой или ребенок очень тяжелый. Рекомендуется использовать средний параметр прирощения угла, сохранив запас мощности сервопривода.");
    Text Text_4("Модель ускорения влияет на переход от максимальной к минимальной задержке поворота. Модель описывается 5 целими или дробными числами. Значения элементов модели уменьшаются слева направо. Модель не допускает использования одинаковых чисел подряд, например: 9.0 5.0 5.0 2.0 1.0 или 9.0 5.5 5.5 2.0 1.0. Если указанная модель не может быть реализована, информация об этом будет отображена в поле \"Состояние\". Всегда указывайте первым число 9 или 9.0, а последним 1 или 1.0.");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get() + Text_4.get());
    Button Button_Back("right", "FAST_MO_SETUP", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_Installation_Auto()
{
    return "";
}
String Page_Installation_AutoHelp()
{
    return "";
}

String Page_User_MainMenu()
{
    ContextHeader ContextHeader_Main(name);
    String programs = "";
    if (event != EVENT_WORK)
    {
        messageUpdateTime = Informer.getDurationInSec();
        RunMessageTimer();
        CreateHeaderUserProg();
        idUserProg.clear();
        list <byte>::iterator i = headerUserProg.begin();
        if (*i > PROG_NUMBER_DEF) // Если базовой программы нет в списке пользовательских программ
        {
            String optionsTitle = "";
            String startTitle = "";
            auto it = catalogHeaderUserProg.find(PROG_NUMBER_DEF);
            if (it != catalogHeaderUserProg.end())
            {
                optionsTitle = "ОПЦИИ<BR>ПРОГРАММЫ<BR>" + it->second;
                startTitle = "ЗАПУСТИТЬ<BR>ПРОГРАММУ<BR>" + it->second;
            }
            else
            {
                optionsTitle = "ОПЦИИ<BR>БАЗОВОЙ<BR>ПРОГРАММЫ";
                startTitle = "ЗАПУСТИТЬ<BR>БАЗОВУЮ<BR>ПРОГРАММУ";
            }
            Button Button_DefaultProgrammOptions("left", "OPTIONS_PROG_" + String(PROG_NUMBER_DEF, DEC), "FORM_MAIN", "ButtonSubmit", optionsTitle);
            Form Form_Button_DefaultProgrammOptions("FORM_MAIN", Button_DefaultProgrammOptions.get());
            Button Button_DefaultProgrammRun("right", "START_PROG_" + String(PROG_NUMBER_DEF, DEC), "FORM_MAIN", "ButtonAction", startTitle);
            Form Form_Button_DefaultProgrammRun("FORM_MAIN", Button_DefaultProgrammRun.get());
            TwoCol TwoCol_default(Form_Button_DefaultProgrammOptions.get() + Form_Button_DefaultProgrammRun.get());
            programs += TwoCol_default.get();
            idUserProg.emplace_back("OPTIONS_PROG_" + String(PROG_NUMBER_DEF, DEC));
            idUserProg.emplace_back("START_PROG_" + String(PROG_NUMBER_DEF, DEC));
        }
        for (; i != headerUserProg.end(); i++)
        {
            // Кнопки опций программ
            String program = "OPTIONS_PROG_";
            program += String(*i, DEC);
            idUserProg.emplace_back(program);
            String title;
            if (*i == PROG_NUMBER_DEF)
            {
                auto it = catalogHeaderUserProg.find(PROG_NUMBER_DEF);
                if (it != catalogHeaderUserProg.end())
                {
                    title = "ОПЦИИ<BR>ПРОГРАММЫ<BR>" + it->second;
                }
                else
                {
                    title = "ОПЦИИ<BR>БАЗОВОЙ<BR>ПРОГРАММЫ";
                }
            }
            else
            {
                auto it = catalogHeaderUserProg.find(*i);
                if (it != catalogHeaderUserProg.end())
                {
                    title = "ОПЦИИ<BR>ПРОГРАММЫ<BR>" + it->second;
                }
                else
                {
                    title = "ОПЦИИ<BR>ПРОГРАММЫ<BR>№ ";
                    String prog = String(*i, DEC);
                    if (*i > 10)
                    {
                        title += prog[1];
                    }
                    title += prog[2];
                }
            }
            Button Button_ProgrammOptions("left", program, "FORM_MAIN", "ButtonSubmit", title);
            Form Form_Button_ProgrammOptions("FORM_MAIN", Button_ProgrammOptions.get());
            // Кнопки запуска программ
            program = "START_PROG_";
            program += String(*i, DEC);
            idUserProg.emplace_back(program);
            if (*i  == PROG_NUMBER_DEF)
            {
                auto it = catalogHeaderUserProg.find(PROG_NUMBER_DEF);
                if (it != catalogHeaderUserProg.end())
                {
                    title = "ЗАПУСТИТЬ<BR>ПРОГРАММУ<BR>" + it->second;
                }
                else
                {
                    title = "ЗАПУСТИТЬ<BR>БАЗОВУЮ<BR>ПРОГРАММУ";
                }
            }
            else
            {
                auto it = catalogHeaderUserProg.find(*i);
                if (it != catalogHeaderUserProg.end())
                {
                    title = "ЗАПУСТИТЬ<BR>ПРОГРАММУ<BR>" + it->second;
                }
                else
                {
                    title = "ЗАПУСТИТЬ<BR>ПРОГРАММУ<BR>№ ";
                    String prog = String(*i, DEC);
                    if (*i > 10)
                    {
                        title += prog[1];
                    }
                    title += prog[2];
                }
            }
            Button Button_ProgrammRun("right", program, "FORM_MAIN", "ButtonAction", title);
            Form Form_Button_ProgrammRun("FORM_MAIN", Button_ProgrammRun.get());
            // Формирование колонок и строк
            TwoCol TwoCol_n(Form_Button_ProgrammOptions.get() + Form_Button_ProgrammRun.get());
            programs += TwoCol_n.get();
        }
    }
    else
    {
        Informer.pop();
        RemainingTime LeftToWork("LEFT_WORK", (workTime * SEC_IN_MIN) - workedTime, "ЗАВЕРШЕНО", 3);
        Informer.add(LeftToWork);
        messageUpdateTime = Informer.getDurationInSec() + 2;
    }
    String status = Informer.get();
    StatusInFrame StatusInFrame_Status("Состояние", status);

    Button Button_Settings("left", "SETTINGS", "FORM_MAIN", "ButtonSubmit", "НАСТРОЙКИ");
    Form Form_Button_Settings("FORM_MAIN", Button_Settings.get());
    String RightOptions;
    String blockedAddButton = "";
    if (event == EVENT_WORK)
    {
        Button Button_BreakWork("right", "BREAK_WORK", "FORM_MAIN", "ButtonCounterAction", "ОСТАНОВИТЬ");
        Form Form_BreakWork("FORM_MAIN", Button_BreakWork.get());
        RightOptions = Form_BreakWork.get();
    }
    else
    {
        Button Button_AddProgramm("right", "ADD_PROGRAMM", "FORM_MAIN", "ButtonSubmit", "ДОБАВИТЬ<BR>ПРОГРАММУ");
        Form Form_Button_AddProgramm("FORM_MAIN", Button_AddProgramm.get());
        RightOptions = Form_Button_AddProgramm.get();
        if (GetLastProg() == PROG_NUMBER_DEF + PROG_LIMIT)
        {
            blockedAddButton = "<script>var buttonAdd = document.getElementById(\"ADD_PROGRAMM\");buttonAdd.disabled = true;buttonAdd.style.backgroundColor = \"#c8c8c8\";document.getElementById(\"ADD_PROGRAMM_1\").className = \"\";</script>";
        }
    }
    TwoCol TwoCol_2(Form_Button_Settings.get() + RightOptions);

    Button Button_Contacts("left", "CONTACTS", "FORM_MAIN", "ButtonSubmit", "КОНТАКТЫ");
    Form Form_Button_Contacts("FORM_MAIN", Button_Contacts.get());
    Button Button_Help("right", "HELP_MAIN", "FORM_MAIN", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_MAIN", Button_Help.get());
    TwoCol TwoCol_3(Form_Button_Contacts.get() + Form_Button_Help.get());

    String script = "<input form=\"FORM_Y_OFFSET\" name=\"SCROLL\" id=\"SCROLL\" type=\"hidden\" value=\"0\"><script>function SendYOffset(){let yOffset = window.pageYOffset || document.documentElement.scrollTop;let form = document.createElement('form');form.id = 'FORM_Y_OFFSET';form.name = 'FORM_Y_OFFSET';form.action = '';form.method = 'POST';document.getElementById('SCROLL').value = yOffset;document.body.append(form);form.submit();}setTimeout(SendYOffset, " + String(messageUpdateTime * 1000, DEC) + ");</script>";

    String body = ContextHeader_Main.get() + script + StatusInFrame_Status.get() + programs + TwoCol_2.get() + blockedAddButton + TwoCol_3.get();
    Html Html_Main(header, body, 0, pageYOffset, animationMain, landscape);
    if(animationMain)
    {
        Html_Main.setCss(CssAnimation.get());
        animationMain = false;
    }
    return Html_Main.get();
}
String Page_User_MainMenuHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("");
    TextContainer TextContainer_1(Text_1.get());
    Button Button_Back("right", "   MAIN_MENU", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_User_ProgramOptions()
{
    String progTitle = "Параметры программы ";
    String progName = "";
    if (progCode == PROG_NUMBER_DEF)
    {
        auto it = catalogHeaderUserProg.find(PROG_NUMBER_DEF);
        if (it != catalogHeaderUserProg.end())
        {
            progTitle += it->second;
            progName = it->second;
        }
        else
        {
            progTitle = "Параметры базовой программы";
        }
    }
    else
    {
        auto it = catalogHeaderUserProg.find(progCode);
        if (it != catalogHeaderUserProg.end())
        {
            progTitle += it->second;
            progName = it->second;
        }
        else
        {
            String prog = String(progCode, DEC);
            if (progCode - PROG_NUMBER_DEF > 10)
            {
                progTitle += prog[1];
            }
            progTitle += prog[2];
        }
    }
    //ContextHeader ContHead((progCode == PROG_NUMBER_DEF) ? "Параметры базовой программы" : "Параметры программы №" + String(progCode - PROG_NUMBER_DEF, DEC));
    ContextHeader ContHead(progTitle);
    LineInputField LineInputField_ProgName("Название программы", "PROG_DESCRIPTION", "FORM_MAIN", progName, "text", false, "[А-Яа-яЁёA-Za-z0-9 ']{1,}", "", "24", "Описание программы", "Описание программы");
    Range Range_WorkTime("Продолжительность работы, мин.", "FORM_MAIN", "WORK_TIME", WORK_TIME_MIN, WORK_TIME_MAX, workTime);
    Range Range_AmpLimiter("Ограничение максимальной амплитуды", "FORM_MAIN", "AMP_LIMIT", LIMIT_MIN, LIMIT_MAX, ampLimit);
    idBuildAmpProg.clear();
    ExtractIdBuildAmpProg();
    String radioAmp = "";
    bool ampSelected1 = false;
    bool ampSelected2 = true;
    list <String>::iterator headAmpIt = headerBuildAmpProg.begin();
    for (auto i = idBuildAmpProg.begin(); i != idBuildAmpProg.end(); i++)
    {
        if (*i == ampCode)
        {
            ampSelected1 = true;
            ampSelected2 = false;
        }
        else
        {
            ampSelected1 = false;
        }
        Radio Radio_AmpProg("AMP_CODE", String(*i, DEC), "FORM_MAIN", ampSelected1, *headAmpIt);
        headAmpIt++;
        radioAmp += Radio_AmpProg.get();
    }
    byte amp;
    if (ampCode > BUILD_AMP_END)
    {
        amp = ampCode;
    }
    else
    {
        amp = GetNextAmpCode();
    }
    Radio Radio_AmpUserProg("AMP_CODE", String(amp, DEC), "FORM_MAIN", ampSelected2, "Пользовательская");
    radioAmp += Radio_AmpUserProg.get();
    CheckRadioContainer CheckRadioCont_Radio_AmpProg("Программа амплитуды", radioAmp);
    String value = "";
    for (auto i = ampProg.begin(); i != ampProg.end(); i++)
    {
        value += String(*i, DEC);
        if (i == --ampProg.end())
        {
            break;
        }
        value += " ";
    }
    LineInputField LineInputField_UserAmpProg("Пользовательская программа амплитуды", "AMP_PROG", "FORM_MAIN", value, "text", true, "[1-9]{,}", "", String(maxSizeArhive, DEC), "1 2 3 4 5 6 7 8 9", "Введите не менне 2-х чисел от 1 до 9 через пробелы");
    ShowHideBlock ShowHideBlock_AmpUserProg(LineInputField_UserAmpProg.get(), "USER_AMP_PROG", Radio_AmpUserProg, "FORM_MAIN", !ampSelected2);

    Range Range_SpeedLimiter("Ограничение максимальной скорости", "FORM_MAIN", "SPEED_LIMIT", LIMIT_MIN, LIMIT_MAX, speedLimit);
    idBuildSpeedProg.clear();
    ExtractIdBuildSpeedProg();
    String radioSpeed = "";
    bool speedSelected1 = false;
    bool speedSelected2 = true;
    list <String>::iterator headSpeedIt = headerBuildSpeedProg.begin();
    for (auto i = idBuildSpeedProg.begin(); i != idBuildSpeedProg.end(); i++)
    {
        if (*i == speedCode)
        {
            speedSelected1 = true;
            speedSelected2 = false;
        }
        else
        {
            speedSelected1 = false;
        }
        Radio Radio_SpeedProg("SPEED_CODE", String(*i, DEC), "FORM_MAIN", speedSelected1, *headSpeedIt);
        headSpeedIt++;
        radioSpeed += Radio_SpeedProg.get();
    }
    byte speed;
    if (speedCode > BUILD_SPEED_END)
    {
        speed = speedCode;
    }
    else
    {
        speed = GetNextSpeedCode();
    }
    Radio Radio_SpeedUserProg("SPEED_CODE", String(speed, DEC), "FORM_MAIN", speedSelected2, "Пользовательская");
    radioSpeed += Radio_SpeedUserProg.get();
    CheckRadioContainer CheckRadioCont_Radio_SpeedProg("Программа скорости", radioSpeed);
    value = "";
    for (auto i = speedProg.begin(); i != speedProg.end(); i++)
    {
        value += String(*i, DEC);
        if (i == --speedProg.end())
        {
            break;
        }
        value += " ";
    }
    LineInputField LineInputField_UserSpeedProg("Пользовательская программа скорости", "SPEED_PROG", "FORM_MAIN", value, "text", true, "[1-9]{,}", "", String(maxSizeArhive, DEC), "1 2 3 4 5 6 7 8 9", "Введите не менне 2-х чисел от 1 до 9 через пробелы");
    ShowHideBlock ShowHideBlock_SpeedUserProg(LineInputField_UserSpeedProg.get(), "USER_SPEED_PROG", Radio_SpeedUserProg, "FORM_MAIN", !speedSelected2);

    String deleteLable = "УДАЛИТЬ";
    if (progCode == PROG_NUMBER_DEF)
    {
        deleteLable = "СБРОСИТЬ";
    }
    Button Button_Delete("left", "DELETE_USER_PROG", "FORM_DELETE", "ButtonSubmit", deleteLable);
    Form Form_Button_Delete("FORM_DELETE", Button_Delete.get());
    Button Button_Help("right", "HELP_USER_PROG", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_HELP", Button_Help.get());
    TwoCol TwoCol1(Form_Button_Delete.get() + Form_Button_Help.get());

    Button Button_Back("left", "MAIN_MENU", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Back("FORM_BACK", Button_Back.get());
    Button Button_Next("right", "SAVE_PROG_OPTIONS", "FORM_MAIN", "ButtonSubmit", "СОХРАНИТЬ");
    Button_Next.setWindowScroll();
    Form Form_Next("FORM_MAIN", Button_Next.get());
    TwoCol TwoCol2(Form_Back.get() + Form_Next.get());
    
    String body = Message("Память заполнена! Уменьшите длину кода пользовательской амплитуды или скорости. Или удалите неиспользуемую программу") + ContHead.get() + LineInputField_ProgName.get() + Range_WorkTime.get() + Range_AmpLimiter.get() + CheckRadioCont_Radio_AmpProg.get() + ShowHideBlock_AmpUserProg.get() + Range_SpeedLimiter.get() + CheckRadioCont_Radio_SpeedProg.get() + ShowHideBlock_SpeedUserProg.get() + TwoCol1.get() + TwoCol2.get();
    Html Html_Main(header, body, 0, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_User_ProgramOptionsHelp()
{
    return "";
}
String Page_User_Settings()
{
    ContextHeader ContextHeader_Main("Пользовательские настройки");

    Button Button_Wireless("left", "WIRELESS_MODE", "FORM_MAIN", "ButtonSubmit", "СЕТЬ");
    Form Form_Button_Wireless("FORM_MAIN", Button_Wireless.get());
    Button Button_Name("right", "NAME", "FORM_MAIN", "ButtonSubmit", "ОПИСАНИЕ");
    Form Form_Button_Name("FORM_MAIN", Button_Name.get());
    TwoCol TwoCol_1(Form_Button_Wireless.get() + Form_Button_Name.get());

    Button Button_MechanicalStart("left", "MECHANICAL_START", "FORM_MAIN", "ButtonSubmit", "РУЧНОЙ<BR>ЗАПУСК");
    Form Form_Button_MechanicalStart("FORM_MAIN", Button_MechanicalStart.get());
    Button Button_VoiceControl("right", "VOICE_CONTROL", "FORM_MAIN", "ButtonSubmit", "ГОЛОСОВОЙ<BR>ЗАПУСК");
    Form Form_Button_VoiceControl("FORM_MAIN", Button_VoiceControl.get());
    TwoCol TwoCol_2(Form_Button_MechanicalStart.get() + Form_Button_VoiceControl.get());

    Button Button_ResetSettings("left", "RESET_SETTINGS", "FORM_MAIN", "ButtonSubmit", "СБРОС");
    Form Form_Button_ResetSettings("FORM_MAIN", Button_ResetSettings.get());
    Button Button_Demo("right", "DEMO_SETUP", "FORM_MAIN", "ButtonSubmit", "ДЕМО");
    Form Form_Button_Demo("FORM_MAIN", Button_Demo.get());
    TwoCol TwoCol_3(Form_Button_ResetSettings.get() + Form_Button_Demo.get());

    Button Button_CalibRestPosition("left", "CALIBRATION_REST", "FORM_MAIN", "ButtonSubmit", "КАЛИБРОВКА");
    Form Form_Button_CalibRestPosition("FORM_MAIN", Button_CalibRestPosition.get());
    Button Button_Back("right", "MAIN_MENU", "FORM_MAIN", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back("FORM_MAIN", Button_Back.get());
    TwoCol TwoCol_4(Form_Button_CalibRestPosition.get() + Form_Button_Back.get());

    String body = ContextHeader_Main.get() + TwoCol_1.get() + TwoCol_2.get() + TwoCol_3.get() + TwoCol_4.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_User_Name()
{
    ContextHeader ContextHeader_Main("Описание кроватки");
    LineInputField LineInputField_Name("Описание детской кроватки", "Name", "FORM_MAIN", name, "text", true, "[A-Za-z0-9 ']{1,}", "", "24", "Имя ребенка", "Не допускаются: длина менее 1-го символа, пробелы в начале и конце, а так-же буквы отличные от латинских.");
    Button Button_Back("left", "SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back("FORM_BACK", Button_Back.get());
    Button Button_Save("right", "SAVE_NAME", "FORM_MAIN", "ButtonSubmit", "СОХРАНИТЬ");
    Form Form_Button_Save("FORM_MAIN", Button_Save.get());
    TwoCol TwoCol(Form_Button_Back.get() + Form_Button_Save.get());
    String body = ContextHeader_Main.get() + LineInputField_Name.get() + TwoCol.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_User_ManualStart()
{
    ContextHeader ContextHeader_Main("Механический старт");

    Radio Radio_HoldInRestTrue("HOLD_IN_REST", "HOLD_TRUE", "FORM_MAIN", holdInRest, "Блокировка качения");
    Radio Radio_HoldInRestFalse("HOLD_IN_REST", "HOLD_FALSE", "FORM_MAIN", !holdInRest, "Свободное качение");
    CheckRadioContainer CheckRadioContainer_HoldInRest("Качение во время ожидания", Radio_HoldInRestTrue.get() + Radio_HoldInRestFalse.get());

    Checkbox Checkbox_StartSwinging("START_SWING", "FORM_MAIN", startSwinging, "Запуск раскачкой");
    Checkbox Checkbox_StartControlled("START_CONT", "FORM_MAIN", startControlled, "Защищеный запуск");
    CheckRadioContainer CheckRadioContainer_TypesOfRelease("Виды механического старта", "TYPES_RELEASE", Checkbox_StartSwinging.get() + Checkbox_StartControlled.get());

    Range Range_StartConfirmationDegrees("Порог раскачивания (градусы)", "FORM_MAIN", "CONF_DEGREES", 10, maxAmplitude, startConfirmationDegrees);
    Range Range_StartConfirmationTime("Время подтверждения (секунды)", "FORM_MAIN", "CONF_TIME", 3, 9, startConfirmationTime);

    Select Select_SwingingProg("FORM_MAIN", "SWING_PROG_NUMB", "SWING_PROG_NUMB", "Программа старта раскачкой");
    std::map <byte, String>::iterator iS = catalogHeaderUserProg.begin();
    if (iS->first != PROG_NUMBER_DEF)
    {
        Select_SwingingProg.setOption(String(PROG_NUMBER_DEF, DEC), "Базовая программа", (iS->first == startSwingingProg) ? true : false);
        String attach = Select_SwingingProg.getSetAttribute("value", String(PROG_NUMBER_DEF, DEC));
        Select_SwingingProg.setOptionScript(String(PROG_NUMBER_DEF, DEC), attach);
    }
    for (auto iS = catalogHeaderUserProg.begin(); iS != catalogHeaderUserProg.end(); iS++)
    {
        String fullName = String(iS->first, DEC);
        String name;
        if (iS->first == PROG_NUMBER_DEF)
        {
            name = "Базовая программа";
        }
        else
        {
            name = "Программа № ";
            for (byte i = 1; i < 3; i++)
            {
                name += fullName[i];
            }
        }
        Select_SwingingProg.setOption(String(iS->first, DEC), name, (iS->first == startSwingingProg) ? true : false);
        String attach = Select_SwingingProg.getSetAttribute("value", String(iS->first, DEC));
        Select_SwingingProg.setOptionScript(String(iS->first, DEC), attach);
    }

    Select Select_ControlledProg("FORM_MAIN", "CONT_PROG_NUMB", "CONT_PROG_NUMB", "Программа защищенного старта");
    std::map <byte, String>::iterator iC = catalogHeaderUserProg.begin();
    if (iC->first != PROG_NUMBER_DEF)
    {
        Select_ControlledProg.setOption(String(PROG_NUMBER_DEF, DEC), "Базовая программа", (iC->first == startControlledProg) ? true : false);
        String attach = Select_ControlledProg.getSetAttribute("value", String(PROG_NUMBER_DEF, DEC));
        Select_ControlledProg.setOptionScript(String(PROG_NUMBER_DEF, DEC), attach);
    }
    for (auto iC = catalogHeaderUserProg.begin(); iC != catalogHeaderUserProg.end(); iC++)
    {
        String fullName = String(iC->first, DEC);
        String name;
        if (iC->first == PROG_NUMBER_DEF)
        {
            name = "Базовая программа";
        }
        else
        {
            name = "Программа № ";
            for (byte i = 1; i < 3; i++)
            {
                name += fullName[i];
            }
        }
        Select_ControlledProg.setOption(String(iC->first, DEC), name, (iC->first == startControlledProg) ? true : false);
        String attach = Select_ControlledProg.getSetAttribute("value", String(iC->first, DEC));
        Select_ControlledProg.setOptionScript(String(iC->first, DEC), attach);
    }

    String scriptHoldInRest = "<script>var types = document.getElementById(\"TYPES_RELEASE\");var swingProg = document.getElementById(\"CONTAINER_SWING_PROG_NUMB\");var contProg = document.getElementById(\"CONTAINER_CONT_PROG_NUMB\");var startCont = document.getElementById(\"START_CONT\");var startSwing = document.getElementById(\"START_SWING\");var cConfTime = document.getElementById(\"CONTAINER_CONF_TIME\");var cConfDeg = document.getElementById(\"CONTAINER_CONF_DEGREES\");let radios = document.getElementsByTagName('input');function ShowHideMechStart(){if(this.name == 'HOLD_IN_REST'){if(this.value == 'HOLD_TRUE'){types.style.display = \"none\";cConfTime.style.display = \"none\";cConfDeg.style.display = \"none\";swingProg.style.display = \"none\";contProg.style.display = \"none\";}else{types.style.display = \"\";if(startCont.checked){cConfTime.style.display = \"\";contProg.style.display = \"\";}if(startSwing.checked){cConfDeg.style.display = \"\";swingProg.style.display = \"\";}}}}for(let i = 0; i < radios.length; i++){radios[i].addEventListener('DOMContentLoaded', ShowHideMechStart);radios[i].addEventListener('click', ShowHideMechStart);}</script>";

    String scriptStartControlled = "<script>function ChangeRequiredSTART_CONT(){START_PROG();if(startCont.checked){cConfTime.style.display = \"\";}else{cConfTime.style.display = \"none\";}}</script>";

    String scriptStartSwinging = "<script>function ChangeRequiredSTART_SWING(){START_PROG();if(startSwing.checked){cConfDeg.style.display = \"\";}else{cConfDeg.style.display = \"none\";}}</script>";

    String scriptStartProg = "<script>function START_PROG(){if(startCont.checked){contProg.style.display = \"\";}else{contProg.style.display = \"none\";}if(startSwing.checked){swingProg.style.display = \"\";}else{swingProg.style.display = \"none\";}}</script>";

    String scriptMechanicalStart = "<script>document.addEventListener('DOMContentLoaded', function(){ChangeRequiredSTART_CONT();ChangeRequiredSTART_SWING();START_PROG();";
    if (holdInRest)
    {
        scriptMechanicalStart += "types.style.display = \"none\";";
    }
    scriptMechanicalStart += "})</script>";

    Button Button_Help("left", "HELP_MECHANICAL_START", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_HELP", Button_Help.get());
    String description = "БЛОКИРОВКА";
    String type = "ButtonAction";
    if (onTimeBlocking)
    {
        description = "СНЯТЬ<BR>БЛОКИРОВКУ";
        type = "ButtonCounterAction";
    }
    Button Button_OnTimeBlocking("right", "ON_TIME_BLOCKING", "FORM_BLOCKING", type, description);
    Form Form_Button_OnTimeBlocking("FORM_BLOCKING", Button_OnTimeBlocking.get());
    TwoCol TwoCol_1(Form_Button_Help.get() + Form_Button_OnTimeBlocking.get());

    Button Button_Back("left", "SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back("FORM_BACK", Button_Back.get());
    Button Button_Save("right", "SAVE_MECHANICAL_START", "FORM_MAIN", "ButtonSubmit", "СОХРАНИТЬ");
    Form Form_Button_Save("FORM_MAIN", Button_Save.get());
    TwoCol TwoCol_2(Form_Button_Back.get() + Form_Button_Save.get());

    String body = ContextHeader_Main.get() + CheckRadioContainer_HoldInRest.get() + CheckRadioContainer_TypesOfRelease.get() + Range_StartConfirmationDegrees.get() + Select_SwingingProg.get() + Range_StartConfirmationTime.get() + Select_ControlledProg.get() + scriptStartControlled + scriptStartSwinging + scriptStartProg + scriptMechanicalStart + scriptHoldInRest + TwoCol_1.get() + TwoCol_2.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_User_VoiceStart()
{
    return "";
}
String Page_User_ResetSettings()
{
    ContextHeader ContextHeader_Main("Сброс настроек");

    Button Button_ResetWireless("left", "RESET_WIRELESS", "FORM_MAIN", "ButtonSubmit", "СЕТЕВЫЕ<BR>НАСТРОЙКИ");
    Form Form_Button_ResetWireless("FORM_MAIN", Button_ResetWireless.get());
    Button Button_ResetUserProg("right", "RESET_PROG", "FORM_MAIN", "ButtonSubmit", "ПОЛЬЗ.<BR>ПРОГРАММЫ");
    Form Form_Button_ResetUserProg("FORM_MAIN", Button_ResetUserProg.get());
    TwoCol TwoCol_1(Form_Button_ResetWireless.get() + Form_Button_ResetUserProg.get());

    Button Button_RestartUserSettings("left", "RESET_USER", "FORM_MAIN", "ButtonSubmit", "ПОЛЬЗ.<BR>НАСТРОЙКИ");
    Form Form_Button_RestartUserSettings("FORM_MAIN", Button_RestartUserSettings.get());
    Button Button_RestartInstallSettings("right", "RESTART_INSTALLATION", "FORM_MAIN", "ButtonSubmit", "УСТАНОВ.<BR>НАСТРОЙКИ");
    Form Form_Button_RestartInstallSettings("FORM_MAIN", Button_RestartInstallSettings.get());
    TwoCol TwoCol_2(Form_Button_RestartUserSettings.get() + Form_Button_RestartInstallSettings.get());

    Button Button_Help("left", "HELP_RESET", "FORM_MAIN", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_MAIN", Button_Help.get());
    Button Button_Back("right", "SETTINGS", "FORM_MAIN", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back("FORM_MAIN", Button_Back.get());
    TwoCol TwoCol_3(Form_Button_Help.get() + Form_Button_Back.get());

    String body = ContextHeader_Main.get() + TwoCol_1.get() + TwoCol_2.get() + TwoCol_3.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_User_ResetSettingsHelp()
{
    ContextHeader ContextHeader_Main("Справка");
    Text Text_1("Пользователю доступны способы частичного и полного сброса настроек.");
    Text Text_2("Для сохранения высокого уровня безопасности любой из доступных сбросов нужно подтвердить физическим контактом (пользовательская кнопка) с устройством укачивания.");
    Text Text_3("В распоряжении пользователя сброс имеются:");
    Text Text_4("1) Сброс настроек беспроводной сети (параметры сети по умолчанию указаны на корпусе устройства).");
    Text Text_5("2) Удаление пользовательских программ укачивания и восстановление предустановленных программ.");
    Text Text_6("3) Сброс всех пользовательских настроек, в которые входят: описание кроватки, беспроводная сеть, пользовательские программы, ручной и голосовой запуск а так-же демонстрационный режим.");
    Text Text_7("4) Сброс всех пользовательских и установочных настроек (ВНИМАНИЕ! Данное действие приведет к неработоспособности устройства до тех пор, пока не будет выполнена установочная настройка. Рекомендуем выполнять эту процедуру только после сервисного обслуживания устройства или в случае установки его на новую маятниковую кроватку.");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get() + Text_3.get() + Text_4.get() + Text_5.get() + Text_6.get() + Text_7.get());
    Button Button_Back("right", "RESET_SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_User_ResetWireless()
{
    ContextHeader ContextHeader_Main("Сброс настроек беспроводной сети");
    Text Text_1("Для сброса настроек беспроводной сети удерживайте пользовательскую кнопку на устройстве более " + String(TIME_CLICK / DELAY_SEC, DEC) + " секунд.");
    TextContainer TextContainer_1(Text_1.get());
    Button Button_Back("right", "RESET_SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, true, landscape);
    Html_Main.setCss(CssAnimation.get());
    return Html_Main.get();
}
String Page_User_ResetProg()
{
    ContextHeader ContextHeader_Main("Сброс пользовательских программ");
    Text Text_1("Для восстановления заводских пользовательских программ удерживайте пользовательскую кнопку на устройстве более " + String(TIME_CLICK / DELAY_SEC, DEC) + " секунд (оставаясь в этом меню).");
    TextContainer TextContainer_1(Text_1.get());
    Button Button_Back("right", "RESET_SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 2, 0, animation, landscape);
    Html_Main.setCss(CssAnimation.get());
    animation = false;
    return Html_Main.get();
}
String Page_User_ResetUser()
{
    ContextHeader ContextHeader_Main("Сброс пользовательских настроек");
    Text Text_1("Эта функция вызовет сброс всех пользовательских настроек: описание кроватки, настройки беспроводной сети, пользовательские программы, параметры механического и голосового старта и демонстрационный режим.");
    Text Text_2("Для сброса пользовательских настроек удерживайте пользовательскую кнопку на устройстве более " + String(TIME_CLICK / DELAY_SEC, DEC) + " секунд (оставаясь в этом меню).");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get());
    Button Button_Back("right", "RESET_SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 2, 0, animation, landscape);
    Html_Main.setCss(CssAnimation.get());
    animation = false;
    return Html_Main.get();
}
String Page_User_ResetInstallation()
{
    ContextHeader ContextHeader_Main("Сброс установочных настроек");
    Text Text_1("Эта функция вызовет сброс всех пользовательских и установочных настроек.");
    Text Text_2("Для сброса установочных настроек удерживайте пользовательскую кнопку на устройстве более " + String(TIME_CLICK / DELAY_SEC, DEC) + " секунд (оставаясь в этом меню).");
    TextContainer TextContainer_1(Text_1.get() + Text_2.get());
    Button Button_Back("right", "RESET_SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back ("FORM_BACK", Button_Back.get());
    TwoCol TwoCol_1(buttonCap + Form_Button_Back.get());
    String body = ContextHeader_Main.get() + TextContainer_1.get() + TwoCol_1.get();
    Html Html_Main(header, body, 2, 0, animation, landscape);
    Html_Main.setCss(CssAnimation.get());
    animation = false;
    return Html_Main.get();
}
String Page_User_Demo()
{
    ContextHeader ContextHeader_Main("Настройки демо режима");
    bool change = false;
    if (demoMode != DEMO_MODE_OFF)
    {
        change = true;
    }
    Checkbox Checkbox_Demo("DEMO", "FORM_SAVE", change, "ДЕМО");
    String inputId[] = {"DURATION_WORK", "DURATION_BREAK"};
    Checkbox_Demo.setRequiredFalse(inputId, 2);
    CheckRadioContainer CheckRadioContainer_Checkbox_Demo("Состояние", Checkbox_Demo.get());
    String dDW = "";
    if (demoDurationWork != 0)
    {
        dDW = String(demoDurationWork, DEC);
    }
    LineInputField LineInputField_DurationWork("Продолжительность работы (мин.)", "DURATION_WORK", "FORM_SAVE", dDW, "number", change, "", "", "2", "", "");
    String dDB = "";
    if (demoDurationBreak != 0)
    {
        dDB = String(demoDurationBreak, DEC);
    }
    LineInputField LineInputField_DurationBreak("Продолжительность перерыва (мин.)", "DURATION_BREAK", "FORM_SAVE", dDB, "number", change, "", "", "2", "", "");
    
    bool checked = false;
    if (demoMode == DEMO_MODE_TIMETABLE)
    {
        checked = !checked;
    }
    Radio Radio_Always("DEMO_MODE", "DEMO_ALWAYS", "FORM_SAVE", !checked, "Все время");
    Radio Radio_Timetable("DEMO_MODE", "DEMO_TIMETABLE", "FORM_SAVE", checked, "По расписанию");
    CheckRadioContainer CheckRadioContainer_DemoMode("Режим работы", Radio_Always.get() + Radio_Timetable.get());
    String content = "Системное время не установлено!";
    if (systemTime != 0)
    {
        int hours;
        int minutes;
        int seconds;
        hours = systemTime / SEC_IN_HOUR;
        minutes = (systemTime - (hours * SEC_IN_HOUR)) / SEC_IN_MIN;
        seconds = systemTime - (hours * SEC_IN_HOUR) - (minutes * SEC_IN_MIN);
        content = "<div id=\"id_server_clock\"></div><script>var hours = " + String(hours, DEC) + ";var minutes = " + String(minutes, DEC) + ";var seconds = " + String(seconds, DEC) + ";var h = hours;var m = minutes;var s = seconds;ServerClock();function ServerClock(){if (hours < 10){h = \"0\" + hours;}else{h = hours;}if (minutes < 10){m = \"0\" + minutes;}else{m = minutes;}if (seconds < 10){s = \"0\" + seconds;}else{s = seconds;}document.getElementById(\"id_server_clock\").innerHTML = h + \":\" + m + \":\" + s;if (++seconds >= 60){seconds = 0;minutes++;if (minutes >= 60){minutes = 0;hours++;if (hours >= 24){hours = 0;}}}setTimeout(\"ServerClock()\", 1000);}</script>";
    }
    StatusInFrame StatusInFrame_SystemTime("Текущее время на сервере (качалка)", content);
    StatusInFrame StatusInFrame_ClientTime("Текущее время на клиенте (Ваше устройство)", "<input type=\"hidden\" form=\"FORM_SYNC\" id=\"HOUR\" name=\"HOUR\" value=\"0\"><input type=\"hidden\" form=\"FORM_SYNC\" id=\"MIN\" name=\"MIN\" value=\"0\"><input type=\"hidden\" form=\"FORM_SYNC\" id=\"SEC\" name=\"SEC\" value=\"0\"><div id=\"id_client_clock\"></div><script>ClientClock();function ClientClock(){var date = new Date();var hours = date.getHours();var minutes = date.getMinutes();var seconds = date.getSeconds();if (hours < 10) hours = \"0\" + hours;if (minutes < 10) minutes = \"0\" + minutes;if (seconds < 10) seconds = \"0\" + seconds;document.getElementById(\"id_client_clock\").innerHTML = hours + \":\" + minutes + \":\" + seconds;document.getElementById('HOUR').value = hours;document.getElementById('MIN').value = minutes;document.getElementById('SEC').value = seconds;setTimeout(\"ClientClock()\", 1000);}</script>");
    LineInputField LineInputField_BeginWork("Начало работы", "BEGIN_DEMO_WORK", "FORM_SAVE", IntToTime(beginTimetableWork), "time", true, "", "", "", "", "");
    LineInputField LineInputField_EndWork("Окончание работы", "END_DEMO_WORK", "FORM_SAVE", IntToTime(endTimetableWork), "time", true, "", "", "", "", "");
    ShowHideBlock ShowHideBlock_Timetable(StatusInFrame_SystemTime.get() + StatusInFrame_ClientTime.get() + LineInputField_BeginWork.get() + LineInputField_EndWork.get(), "BLOCK_TIMETABLE", Radio_Timetable, "DEMO_TIMETABLE", !checked);

    Button Button_Help("left", "HELP_DEMO", "FORM_HELP", "ButtonSubmit", "СПРАВКА");
    Form Form_Button_Help("FORM_HELP", Button_Help.get());
    Button Button_Sync("right", "SYNC_SYSTEM_TIME", "FORM_SYNC", "ButtonSubmit", "СИНХ.<BR>ВРЕМЯ");
    Button_Sync.setWindowScroll();
    Form Form_Button_Sync("FORM_SYNC", Button_Sync.get());
    TwoCol TwoCol_1(Form_Button_Help.get() + Form_Button_Sync.get());

    Button Button_Back("left", "SETTINGS", "FORM_BACK", "ButtonSubmit", "НАЗАД");
    Form Form_Button_Back("FORM_BACK", Button_Back.get());
    Button Button_Save("right", "SAVE_DEMO", "FORM_SAVE", "ButtonSubmit", "СОХРАНИТЬ");
    Button_Save.setWindowScroll();
    Form Form_Button_Save("FORM_SAVE", Button_Save.get());
    TwoCol TwoCol_2(Form_Button_Back.get() + Form_Button_Save.get());

    String blockedSyncButton;
    if (clockOn || demoMode == DEMO_MODE_TIMETABLE)
    {
        blockedSyncButton = "<script>var radios = document.getElementsByTagName('input');for(var i = 0; i < radios.length; i++){radios[i].addEventListener('click', Blocked);function Blocked(){if(this.name == 'DEMO_MODE'){if(this.value == 'DEMO_ALWAYS'){document.getElementById(\"SYNC_SYSTEM_TIME\").disabled = true;document.getElementById(\"SYNC_SYSTEM_TIME\").style.backgroundColor = \"#c8c8c8\";document.getElementById(\"SYNC_SYSTEM_TIME_1\").className = \"\";} else {document.getElementById(\"SYNC_SYSTEM_TIME\").disabled = false;document.getElementById(\"SYNC_SYSTEM_TIME\").style.backgroundColor = \"#4E617A\";document.getElementById(\"SYNC_SYSTEM_TIME_1\").className = \"ButtonAnimationPosition ButtonSubmit\";}}}}</script>";
    }
    else
    {
        blockedSyncButton = "<script>document.getElementById(\"SYNC_SYSTEM_TIME\").disabled = true;document.getElementById(\"SYNC_SYSTEM_TIME\").style.backgroundColor = \"#c8c8c8\";document.getElementById(\"SYNC_SYSTEM_TIME_1\").className = \"\";</script>";
    }
    String currentTime = "<input type=\"hidden\" form=\"FORM_SAVE\" id=\"C_HOUR\" name=\"C_HOUR\" value=\"0\"><input type=\"hidden\" form=\"FORM_SAVE\" id=\"C_MIN\" name=\"C_MIN\" value=\"0\"><input type=\"hidden\" form=\"FORM_SAVE\" id=\"C_SEC\" name=\"C_SEC\" value=\"0\"><script>GetClientClock();function GetClientClock(){var date = new Date();var hours = date.getHours();var minutes = date.getMinutes();var seconds = date.getSeconds();if (hours < 10) hours = \"0\" + hours;if (minutes < 10) minutes = \"0\" + minutes;if (seconds < 10) seconds = \"0\" + seconds;document.getElementById('C_HOUR').value = hours;document.getElementById('C_MIN').value = minutes;document.getElementById('C_SEC').value = seconds;setTimeout(\"GetClientClock()\", 1000);}</script>";

    String body = ContextHeader_Main.get() + CheckRadioContainer_Checkbox_Demo.get() + LineInputField_DurationWork.get() + LineInputField_DurationBreak.get() + CheckRadioContainer_DemoMode.get() + ShowHideBlock_Timetable.get() + TwoCol_1.get() + TwoCol_2.get() + blockedSyncButton + currentTime;
    Html Html_Main(header, body, 0, pageYOffset, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}
String Page_User_CalibrateAmplitude()
{
    ContextHeader ContextHeader_Main("Калибровка положения покоя");
    SERVO_MAIN.attach();
    RELAY_MAIN.set(ENABLE);
    SERVO_MAIN.setRelativeMiddle(true);
    StatusInFrame StatusInFrame_Degrees("Угол положения покоя", String(SERVO_MAIN.getActualAngle(), DEC) + "&deg");
    SERVO_MAIN.setRelativeMiddle(false);
    event = EVENT_SHUTDOWN;
    Button Button_Back("left", "SETTINGS", "FORM_MAIN", "ButtonSubmit", "НАЗАД");
    Button Button_Meashure("right", "MEASHURE_REST", "FORM_MAIN", "ButtonAction", "ЗАМЕРИТЬ");
    Form Form_Main("FORM_MAIN", Button_Back.get() + Button_Meashure.get());
    TwoCol TwoCol_1(Form_Main.get());
    String body = ContextHeader_Main.get() + StatusInFrame_Degrees.get() + TwoCol_1.get();
    Html Html_Main(header, body, 0, 0, animation, landscape);
    if(animation)
    {
        Html_Main.setCss(CssAnimation.get());
    }
    return Html_Main.get();
}