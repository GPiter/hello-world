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
using System.Xml.Serialization;

namespace patient_profile
{
    /// <summary>
    /// Логика взаимодействия для Page2.xaml
    /// </summary>
    public partial class Page2 : Page
    {
        int slider_value;                   // Переменная для хранения значения слайдера
        string writePath = @"D:\test.txt";  // Директория записи в файл

        public Page2()
        {
            InitializeComponent();
            CheckBase();
        }

        // Привязка к странице 1 при нажатии кнопки "Назад"
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Page1 p1 = new Page1();
            this.NavigationService.Navigate(p1);
        }

        //------------------------------ Обработка значений слайдеров --------------------------------//

        private void Sl_answer3_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            slider_value = (int)sl_answer3.Value;
            WorkBase.anket_base[2] = slider_value.ToString();
        }

        private void Sl_answer4_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            slider_value = (int)sl_answer4.Value;
            WorkBase.anket_base[3] = slider_value.ToString();
        }

        private void Sl_answer5_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            slider_value = (int)sl_answer5.Value;
            WorkBase.anket_base[4] = slider_value.ToString();
        }

        private void Sl_answer6_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            slider_value = (int)sl_answer6.Value;
            WorkBase.anket_base[5] = slider_value.ToString();
        }

        private void Sl_answer7_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            slider_value = (int)sl_answer7.Value;
            WorkBase.anket_base[6] = slider_value.ToString();
        }

        private void Sl_answer8_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            slider_value = (int)sl_answer8.Value;
            WorkBase.anket_base[7] = slider_value.ToString();
        }

        private void Sl_answer9_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            slider_value = (int)sl_answer9.Value;
            WorkBase.anket_base[8] = slider_value.ToString();
        }

        //-------------------------------------------------------------------------------------------//

        //-------------------------------- Обработка конпки "Далее" ---------------------------------//
        private void BtnNext_p2_Click(object sender, RoutedEventArgs e)
        {
            // Запись ответов в XML

            XmlSerializer serializer = new XmlSerializer(typeof(item[]),
            new XmlRootAttribute() { ElementName = "items" });

            using (FileStream fs = new FileStream("anket_answers.xml", FileMode.OpenOrCreate))
            {
                serializer.Serialize(fs,
                WorkBase.anket_base.Select(kv => new item() { id = kv.Key, value = kv.Value }).ToArray());
            }

            // Привязка к странице 3 при нажатии кнопки "Далее"
            Page3 p3 = new Page3();
            this.NavigationService.Navigate(p3);
        }

        //-------------------------------------------------------------------------------------------//

        //-------------------- Проверка на содержимое базы ответов -------------------//
        private void CheckBase()
        {
            if (WorkBase.anket_base.ContainsKey(2))
            {
                sl_answer3.Value = Convert.ToDouble(WorkBase.anket_base[2]);
            }

            if (WorkBase.anket_base.ContainsKey(3))
            {
                sl_answer4.Value = Convert.ToDouble(WorkBase.anket_base[3]);
            }

            if (WorkBase.anket_base.ContainsKey(4))
            {
                sl_answer5.Value = Convert.ToDouble(WorkBase.anket_base[4]);
            }

            if (WorkBase.anket_base.ContainsKey(5))
            {
                sl_answer6.Value = Convert.ToDouble(WorkBase.anket_base[5]);
            }

            if (WorkBase.anket_base.ContainsKey(6))
            {
                sl_answer7.Value = Convert.ToDouble(WorkBase.anket_base[6]);
            }

            if (WorkBase.anket_base.ContainsKey(7))
            {
                sl_answer8.Value = Convert.ToDouble(WorkBase.anket_base[7]);
            }

            if (WorkBase.anket_base.ContainsKey(8))
            {
                sl_answer9.Value = Convert.ToDouble(WorkBase.anket_base[8]);
            }
        }

        //----------------------------------------------------------------------------//

    }
}
