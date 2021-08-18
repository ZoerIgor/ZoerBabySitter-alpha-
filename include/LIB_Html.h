#pragma once
#ifndef _LIB_HTML_H_
    #define _LIB_HTML_H_
    #include <Arduino.h>
    #include <queue>
    #include <vector>
    using namespace std;
    #define MILLIS_IN_SEC 1000
    #define UPDATE_TIME_IN_SEC 60
    // Информер
        class Info
        {
            public:
                virtual String getContent() = 0;
                virtual byte getPriority() = 0;
                virtual int getDurationInSec() = 0;
        };
        class RemainingTime: public Info
        {
            public:
                RemainingTime(String id, const short &timeInSec, String endMsg, byte priority);
                String getContent() override;
                byte getPriority() override;
                int getDurationInSec() override;
            private:
                byte _priority;
                short _timeInSec;
                String _id, _endMsg;
        };
        class Ticker: public Info
        {
            public:
                Ticker(String id, String attachment, short visibleArea, byte priority);
                Ticker(String id, String attachment, short visibleArea, byte priority, byte spaceCount, short updateTime, short pauseTime);
                static void setUpdateGeneralTimeInSec(short time);
                static void setStaticVar(byte spaceCount, short updateTime, short pauseTime);
                String getContent() override;
                byte getPriority() override;
                int getDurationInSec() override;
            private:
                static byte _spaceCountStatic;
                static short _updateTimeStatic, _pauseTimeStatic, _updateGeneralTimeStatic;
                byte _spaceCount, _priority;
                short _visibleArea, _updateTime, _pauseTime;
                String _id, _attachment;
        };
        class InfoQueue
        {
            class Data;
            public:
                void setAutoAddPriority(byte priority);
                void setAutoClearPriority(byte priority);
                void setEmptyQueueMessage(String message);
                void setUpdateTimeInSec(short time);
                void add(Info &info);
                void add(Data &data);
                String get();
                void pop();
                void automatic();
                int getDurationInSec();
            private:
                class Data
                {
                    public:
                        Data(Info &info);
                        String getContent();
                        byte getPriority();
                        int getDurationInSec();
                    private:
                        byte _priority;
                        int _durationInSec;
                        String _data;
                };
                struct Compare
                {
                    bool operator()(Data &dataA, Data &dataB);
                };
                #define PRIORITY_ADD 1
                #define PRIORITY_CLEAR 2
                byte _autoAddPriority = PRIORITY_ADD, _autoClearPriority = PRIORITY_CLEAR;
                short _updateTime = UPDATE_TIME_IN_SEC;
                priority_queue <Data, vector <Data>, Compare> _pq;
                String _queueEmpty = "Message queue is empty";
        };
    // Заглушка кнопки
        extern const String buttonCap;
    // Подсключаемые стили CSS
        class Css
        {
            public:
                Css(String attachment);
                String get();
            private:
                String _css;
        };
    // Статическое начало страницы
        class Html
        {
            public:
                Html(String title, String attachment, int refresh, short pageYOffset, bool animation, bool ladscape);
                void setCss(String attachment);
                String get();
            private:
                bool _animation, _landscape;
                short _pageYOffset;
                int _refresh;
                String _title, _attachment, _css;
        };
    // Контекстный заголовок
        class ContextHeader
        {
            public:
                ContextHeader(String header);
                String get();
            private:
                String contextHeader;
        };
    // Ссылка в рамке
        class ReferenceInFrame
        {
            public:
                ReferenceInFrame(String header, String protocol, String value);
                ReferenceInFrame(String header, String protocol, String value, String mailSubject, String mailBody);
                String get();
            private:
                String referenceInFrame;
        };
    // Отображение состояния
        class StatusInFrame
        {
            public:
                StatusInFrame(String header, String value);
                StatusInFrame(String header, byte value, String measure);
                String get();
            private:
                String statusInFrame;
        };
    // Форма
        class Form
        {
            public:
                Form(String id, String attachment);
                String get();
            private:
                String form;
        };
    // Отображение блока
        class Radio;
        class Button;
        class Checkbox;
        class ShowHideBlock
        {
            public:
                ShowHideBlock(String attachment, String blockId, Checkbox &checkbox, bool hide);
                ShowHideBlock(String attachment, String blockId, bool hide);
                ShowHideBlock(Button &button, String blockId, String titleShow, bool hide);
                ShowHideBlock(String attachment, String blockId, Radio &radio, String formId, bool hide);
                ShowHideBlock(Radio &radio, String hideId, bool show);
                String get();
            private:
                String Before();
                String After();
                String View();
                String blockId, attachment, showHideBlock;
                bool hide;
        };
    // Контейнер переключателей
        class CheckRadioContainer
        {
            public:
                CheckRadioContainer(String lable, String attachment);
                CheckRadioContainer(String lable, String id, String attachment);
                String get();
            private:
                String checkRadioContainer;
        };
    // Флажок
        class Checkbox
        {
            public:
                Checkbox(String name, String form, bool checked, String header);
                void setRequiredFalse(String idInputs[], byte size);
                String get();
            private:
                String getId();
                String name, checkbox, _script;
                friend ShowHideBlock::ShowHideBlock(String attachment, String blockId, Checkbox &checkbox, bool hide);
        };
    // Переключатель
        class Radio
        {
            public:
                Radio(String name, String value, String form, bool checked, String header);
                String get();
                String getId();
                String getValue();
            private:
                String name, value, radio;
                friend ShowHideBlock::ShowHideBlock(String attachment, String blockId, Radio &radio, String formId, bool hide);
        };
    // Строчное поле ввода
        class LineInputField
        {
            public:
                LineInputField(String header, String id, String formId, String value, String type, bool required, String pattern = "", String onKeyUp = "", String maxLenght = "", String placeHolder = "", String title = "");
                LineInputField(String id, String formId, String value);
                void setEncrypt(String attachment);
                String getHide();
                String get();
                String getId();
            private:
                bool _required;
                String _header, _id, _formId, _value, _type, _pattern, _onKeyUp, _maxLenght, _placeHolder, _title, _lineInputField , _encrypt;
        };
    // Две колонки
        class TwoCol
        {
            public:
                TwoCol(String attachment);
                String get();
            private:
                String twoCol;
        };
    // Кнопка
        class Button
        {
            public:
                Button(String align, String id, String formId, String type, String title);
                void setWindowScroll();
                void setFreeFormInput(String idInput, String value);
                void setAlert(String alert);
                String get();
            private:
                String getId();
                String getTitle();
                float getPadding(String _title);
                String id, idInput, formId, title, button, beginScript, endScript;
                friend ShowHideBlock::ShowHideBlock(Button &button, String blockId, String titleShow, bool hide);
        };
    // Квадратное поле ввода
        class QuadroInputField
        {
            public:
                QuadroInputField(String align, String name, String form, String value, bool required, String maxLenght, String min, String max, String placeHolder, String onKeyUp, String onChange, String script);
                String get();
            private:
                String quadroInputField;
        };
    // Выпадающий список
        class Select
        {
            public:
                Select(String formId, String ownId, String targetId, String title);
                void setOption(String value, String title, bool selected);
                String getSetAttribute(String atributeName, String atributevalue);
                String getSetAttribute(String row, String atributeName, String atributevalue);
                String getRemoveAttribute(String nameAttribute);
                void setOptionScript(String value, String attachment);
                String get();
            private:
                bool _firstScript;
                String _select, _script, _ownId, _targetId;
        };
    // Ползунок
        class Range
        {
            public:
                Range(String lable, String form, String id, int min, int max, int value);
                String get();
            private:
                String range;
        };
    // Контейнер списка
        class ListContainer
        {
            public:
                ListContainer(String attachment);
                String get();
            private:
                String listContainer;
        };
    // Тело списка
        class List
        {
            public:
                List(String id, String header);
                String get();
            private:
                String list;
        };
    // Контейнер для текста
        class TextContainer
        {
            public:
                TextContainer(String attachment);
                String get();
            private:
                String textContainer;
        };
    // Заголовок текста
        class TextHeader
        {
            public:
                TextHeader(String header);
                String get();
            private:
                String textHeader;
        };
    // Подзаголовок текста
        class TextSubHeader
        {
            public:
                TextSubHeader(String header);
                String get();
            private:
                String textSubHeader;
        };
    // Текст
        class Text
        {
            public:
                Text(String newText);
                String get();
            private:
                String text;
        };
    // Таблица
        class Table
        {
            public:
                Table();
                void set(String row);
                String get();
            private:
                String table, openTag, closeTag;
        };
    // Диалоговое окно
        class Alert
        {
            public:
                Alert(String message);
                void set(String message);
                String get();
            private:
                String _alert;
        };
#endif