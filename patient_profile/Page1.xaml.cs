using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;

namespace patient_profile
{
    /// <summary>
    /// Логика взаимодействия для Page1.xaml
    /// </summary>
    public partial class Page1 : Page
    {
        int slider_value;                   // Переменная для хранения значения слайдера
        string writePath = @"D:\test.txt";  // Директория записи в файл

        public Page1()
        {
            InitializeComponent();
        }

        //------------------------ Обработка радиобаттонов ----------------------------//
        private void Rb1_Checked(object sender, RoutedEventArgs e)
        {
            WorkBase.anket_base[0] = cb_answer1_1.Content.ToString();
        }

        private void Rb2_Checked(object sender, RoutedEventArgs e)
        {
            WorkBase.anket_base[0] = cb_answer1_2.Content.ToString();
        }

        private void Rb3_Checked(object sender, RoutedEventArgs e)
        {
            WorkBase.anket_base[0] = cb_answer1_3.Content.ToString();
        }

        private void Rb4_Checked(object sender, RoutedEventArgs e)
        {
            WorkBase.anket_base[0] = cb_answer1_4.Content.ToString();
        }

        //----------------------------------------------------------------------------//


        //------------------------- Обработка слайдера -------------------------------//

        private void Sl_answer_ValueChanged(object sender, RoutedEventArgs e)
        {
            slider_value = (int)sl_answer2_1.Value;
            WorkBase.anket_base[1] = slider_value.ToString();
        }

        //----------------------------------------------------------------------------//


        //------------------------- Обработка конпки "Далее" -------------------------//
        private void BtnNext_Click(object sender, RoutedEventArgs e)
        {
            // Запись в файл
            try
            {
                using (StreamWriter sw = new StreamWriter(writePath, false, System.Text.Encoding.Default))
                {
                    sw.WriteLine(WorkBase.anket_base[0]);
                    sw.WriteLine(WorkBase.anket_base[1]);
                }
            }

            catch (Exception)
            {
                MessageBox.Show("Ошибка при записи в файл!");
            }

            // Привязка к странице 3 при нажатии кнопки "Далее"
            Page2 p2 = new Page2();
            this.NavigationService.Navigate(p2);
        }

        //----------------------------------------------------------------------------//

    }
}
