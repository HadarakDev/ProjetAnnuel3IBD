using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using System.Diagnostics;

namespace YoutubeImageDataset
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnExitProgram_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private bool checkError(int full = 1)
        {
            string error = "";
            if (SelectedSourceFolder.Text.Equals("No Source"))
            {
                error += " - No source selected \r\n";
            }

            if (SelectedDestinationFolder.Text.Equals("No Destination"))
            {
                error += " - No destination selected \r\n";
            }
            if (full == 1 && SelectGender.SelectedIndex == -1)
            {
                error += " - No Gender selected \r\n";
            }

            if (full == 1 && SelectRace.SelectedIndex == -1)
            {
                error += " - No Race selected \r\n";
            }

            if (error == String.Empty)
            {
                ErrorLabel.Text = "No Error";
                ErrorLabel.ForeColor = Color.Green;
                return (true);
            }
            else
            {
                ErrorLabel.Text = error;
                ErrorLabel.ForeColor = Color.Red;
                return (false);
            }
        }

        private void ConvertImages_Click(object sender, EventArgs e)
        {
            if (checkError() == false)
                return;
            string destPath = SelectedDestinationFolder.Text;
            string sourcePath = SelectedSourceFolder.Text;
            string race = SelectRace.SelectedItem.ToString();
            string gender = SelectGender.SelectedItem.ToString();
            ConvertImages.Enabled = false;
            try
            {
                if (useInterval.Checked)
                {
                    if ((ConvertImagesWithInterval(destPath, sourcePath, gender, race)) == -1)
                    {
                        ConvertImages.Enabled = true;
                        return; //erreur;
                    }
                }
                else
                {
                    if ((ConvertImagesWithFolderName(destPath, sourcePath, gender, race)) == -1)
                    {
                        ConvertImages.Enabled = true;
                        return; //erreur;
                    }
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }

            ConvertImages.Enabled = true;
        }

        private int ConvertImagesWithFolderName(string destPath, string sourcePath, string gender, string race) // Lotte
        {
            string[] dirs = Directory.GetDirectories(sourcePath);
            var dirList = from x in dirs orderby x.Length, x select x;
            
            int id = 0;
            foreach (var dir in dirList)
            {
                Program.RemoveDoubles(dir);
                string[] files = Directory.GetFiles(dir);
                string age = Path.GetFileName(dir);
                foreach (string file in files)
                {
                    try
                    {
                        File.Copy(file, destPath + age + "_" + gender + "_" + race + "_0_" + id + ".jpg");// date == 0
                    }
                    catch (Exception ex)
                    {
                        Debug.WriteLine(ex.Message);
                        return (-1);
                    }
                    id++;
                }
            }
            return (0);
        }

        private int ConvertImagesWithInterval(string destPath, string sourcePath, string gender, string race) // Stephanie
        {
            int id = 0;
            Program.RemoveDoubles(sourcePath);
            string[] files = Directory.GetFiles(sourcePath);
            int days = 0;
            int age = 0;

            try {
                Int32.TryParse(startAgeTextBox.Text, out age);
            }
            catch (Exception ex) {
                Debug.WriteLine(ex.Message);
                return (-1);
            }
            
            int interval;
            try {
                Int32.TryParse(intervalTextBox.Text, out interval);
            }
            catch (Exception ex) {
                Debug.WriteLine(ex.Message);
                return (-1);
            }

            foreach (string file in files)
            {
                try
                {
                    File.Copy(file, destPath + age.ToString() + "_" + gender + "_" + race + "_0_" + id + ".jpg");// date == 0
                    days += interval;
                    if (days >= 365)
                    {
                        days = 0;
                        age++;
                    }
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                }
                id++;
            }
            return (0);
        }

        private void SelectDestination_Click_1(object sender, EventArgs e)
        {
            FolderBrowserDialog fd = new FolderBrowserDialog();
            fd.RootFolder = Environment.SpecialFolder.Desktop;

            if (fd.ShowDialog() == DialogResult.OK)
            {
                SelectedDestinationFolder.Text = fd.SelectedPath + "\\";
            }

        }

        private void SelectSource_Click_1(object sender, EventArgs e)
        {
            FolderBrowserDialog fd = new FolderBrowserDialog();
            fd.RootFolder = Environment.SpecialFolder.Desktop;

            if (fd.ShowDialog() == DialogResult.OK)
            {
                SelectedSourceFolder.Text = fd.SelectedPath + "\\";
            }
        }

        private void OpenCropper_Click(object sender, EventArgs e)
        {
            Form f2 = new Form2();

            if (checkError(0) == false)
                return;
            f2.Show();
            ErrorLabel.ForeColor = Color.Green;
            string sourcePath = SelectedSourceFolder.Text;
            string[] files = Directory.GetFiles(sourcePath);
            Image img = Image.FromFile(files[0]);
            Size size = new Size(img.Width, img.Height);
            Application.OpenForms["Form2"].Controls["pictureBox"].Size = size;
            Application.OpenForms["Form2"].Controls["pictureBox"].BackgroundImage = img;



        }
    }
}
