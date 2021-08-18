#pragma once
#ifndef AKIMA_SPLINE_H
    #define AKIMA_SPLINE_H
    #include <Arduino.h>
    namespace cs
    {

        class AkimaSplineBase
        {
            public:
                AkimaSplineBase(){};
                AkimaSplineBase(const std::vector<float> &x, const std::vector<float> &y)
                {
                    set_points(x, y);
                };
                ~AkimaSplineBase()
                {
                    std::vector<float>().swap(raw_slopes);
                    std::vector<float>().swap(argmented_slopes);
                    std::vector<float>().swap(m_x);
                    std::vector<float>().swap(m_y);
                    std::vector<float>().swap(m_b);
                    std::vector<float>().swap(m_c);
                    std::vector<float>().swap(m_d);
                    std::vector<float>().swap(num_count);
                    std::vector<float>().swap(bin_idx);
                    std::vector<float>().swap(diff_x);
                    std::vector<float>().swap(diff_y);
                    std::vector<float>().swap(diff_argmented_slopes);
                    std::vector<float>().swap(f1);
                    std::vector<float>().swap(f2);
                    std::vector<float>().swap(f12);
                    constructed_flag = false;
                    error = false;
                    data_length = 0;
                };
                bool set_points(const std::vector<float> &x, const std::vector<float> &y);
                void generate_points(std::vector<float> &x, std::vector<float> &y);
                void set_error(bool error);
                bool constructed_flag, error;
            private:
                std::vector<float> raw_slopes, argmented_slopes, m_x, m_y, m_b, m_c, m_d, num_count, bin_idx, diff_x, diff_y, diff_argmented_slopes, f1, f2, f12;
                int data_length;
                void diff(std::vector<float> &val, std::vector<float> &diff_val);
                bool validity_check();
                void hist_count(std::vector<float> &x, std::vector<int> &num_count, std::vector<int> &bin, std::vector<int> &bb);
        };
        class AkimaSpline 
        {
            public:
                AkimaSpline(){};
                AkimaSpline(std::vector<float> &x, std::vector<float> &y, int &t_num)
                {
                    _m_x = x;
                    _m_y = y;
                    _t_num = t_num;
                    generate_t_internal();
                    generate_t_out();
                };
                ~AkimaSpline()
                {
                    std::vector<short>().swap(x_out);
                    std::vector<short>().swap(y_out);
                    std::vector<float>().swap(_t_internal);
                    std::vector<float>().swap(_t_out);
                    std::vector<float>().swap(_x_between);
                    std::vector<float>().swap(_y_between);
                    std::vector<float>().swap(_x_out);
                    std::vector<float>().swap(_y_out);
                    std::vector<float>().swap(_m_x);
                    std::vector<float>().swap(_m_y);
                    constructed_flag = false;
                    _data_length = 0;
                    _t_num = 0;
                };
                void generate_t_internal();
                void generate_t_out();
                bool init(std::vector<float> &x, std::vector<float> &y, int t_num);
                bool proc();
                bool validity_check();
                bool constructed_flag;
                std::vector<short> x_out, y_out;  
            private:
                AkimaSplineBase _x_spline, _y_spline;
                void correc_points(const std::vector<float> &x_in, const std::vector<float> &y_in, std::vector<float> &x_out, std::vector<float> &y_out);
                std::vector<float> _t_internal, _t_out, _x_between, _y_between, _x_out, _y_out, _m_x, _m_y;
                int _data_length, _t_num;
        };
    }
#endif