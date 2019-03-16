﻿namespace YoutubeImageDataset
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.ConvertImages = new System.Windows.Forms.Button();
            this.SelectSource = new System.Windows.Forms.Button();
            this.SelectedSourceFolder = new System.Windows.Forms.Label();
            this.SelectedDestinationFolder = new System.Windows.Forms.Label();
            this.SelectDestination = new System.Windows.Forms.Button();
            this.SelectGender = new System.Windows.Forms.ComboBox();
            this.selectGenderLabel = new System.Windows.Forms.Label();
            this.SelectRaceLabel = new System.Windows.Forms.Label();
            this.SelectRace = new System.Windows.Forms.ComboBox();
            this.ErrorLabel = new System.Windows.Forms.Label();
            this.startAgeTextBox = new System.Windows.Forms.TextBox();
            this.SelectStartAgeLabel = new System.Windows.Forms.Label();
            this.SelectIntervalLabel = new System.Windows.Forms.Label();
            this.intervalTextBox = new System.Windows.Forms.TextBox();
            this.useInterval = new System.Windows.Forms.CheckBox();
            this.OpenCropper = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // ConvertImages
            // 
            this.ConvertImages.Location = new System.Drawing.Point(1148, 721);
            this.ConvertImages.Name = "ConvertImages";
            this.ConvertImages.Size = new System.Drawing.Size(244, 72);
            this.ConvertImages.TabIndex = 0;
            this.ConvertImages.Text = "Convert Images";
            this.ConvertImages.UseVisualStyleBackColor = true;
            this.ConvertImages.Click += new System.EventHandler(this.ConvertImages_Click);
            // 
            // SelectSource
            // 
            this.SelectSource.Location = new System.Drawing.Point(90, 120);
            this.SelectSource.Name = "SelectSource";
            this.SelectSource.Size = new System.Drawing.Size(326, 60);
            this.SelectSource.TabIndex = 1;
            this.SelectSource.Text = "Select Screenshot source";
            this.SelectSource.UseVisualStyleBackColor = true;
            this.SelectSource.Click += new System.EventHandler(this.SelectSource_Click_1);
            // 
            // SelectedSourceFolder
            // 
            this.SelectedSourceFolder.Location = new System.Drawing.Point(872, 120);
            this.SelectedSourceFolder.Name = "SelectedSourceFolder";
            this.SelectedSourceFolder.Size = new System.Drawing.Size(577, 60);
            this.SelectedSourceFolder.TabIndex = 2;
            this.SelectedSourceFolder.Text = "No Source";
            this.SelectedSourceFolder.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // SelectedDestinationFolder
            // 
            this.SelectedDestinationFolder.Location = new System.Drawing.Point(872, 212);
            this.SelectedDestinationFolder.Name = "SelectedDestinationFolder";
            this.SelectedDestinationFolder.Size = new System.Drawing.Size(561, 60);
            this.SelectedDestinationFolder.TabIndex = 4;
            this.SelectedDestinationFolder.Text = "No Destination";
            this.SelectedDestinationFolder.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // SelectDestination
            // 
            this.SelectDestination.Location = new System.Drawing.Point(90, 228);
            this.SelectDestination.Name = "SelectDestination";
            this.SelectDestination.Size = new System.Drawing.Size(326, 60);
            this.SelectDestination.TabIndex = 6;
            this.SelectDestination.Text = "Select Screenshot destination";
            this.SelectDestination.UseVisualStyleBackColor = true;
            this.SelectDestination.Click += new System.EventHandler(this.SelectDestination_Click_1);
            // 
            // SelectGender
            // 
            this.SelectGender.DropDownHeight = 200;
            this.SelectGender.DropDownWidth = 250;
            this.SelectGender.FormattingEnabled = true;
            this.SelectGender.IntegralHeight = false;
            this.SelectGender.Items.AddRange(new object[] {
            "0",
            "1"});
            this.SelectGender.Location = new System.Drawing.Point(877, 337);
            this.SelectGender.Name = "SelectGender";
            this.SelectGender.Size = new System.Drawing.Size(500, 33);
            this.SelectGender.TabIndex = 7;
            this.SelectGender.Text = "0 (male) or 1 (female)";
            // 
            // selectGenderLabel
            // 
            this.selectGenderLabel.Location = new System.Drawing.Point(90, 322);
            this.selectGenderLabel.Name = "selectGenderLabel";
            this.selectGenderLabel.Size = new System.Drawing.Size(326, 61);
            this.selectGenderLabel.TabIndex = 8;
            this.selectGenderLabel.Text = "Select Gender";
            this.selectGenderLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // SelectRaceLabel
            // 
            this.SelectRaceLabel.Location = new System.Drawing.Point(90, 402);
            this.SelectRaceLabel.Name = "SelectRaceLabel";
            this.SelectRaceLabel.Size = new System.Drawing.Size(326, 61);
            this.SelectRaceLabel.TabIndex = 9;
            this.SelectRaceLabel.Text = "Select Race";
            this.SelectRaceLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // SelectRace
            // 
            this.SelectRace.DropDownHeight = 200;
            this.SelectRace.DropDownWidth = 250;
            this.SelectRace.FormattingEnabled = true;
            this.SelectRace.IntegralHeight = false;
            this.SelectRace.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4"});
            this.SelectRace.Location = new System.Drawing.Point(877, 402);
            this.SelectRace.Name = "SelectRace";
            this.SelectRace.Size = new System.Drawing.Size(500, 33);
            this.SelectRace.TabIndex = 10;
            this.SelectRace.Text = "0 White, 1 Black, 2 Asian,  3Indian, 4 Others";
            // 
            // ErrorLabel
            // 
            this.ErrorLabel.ForeColor = System.Drawing.Color.Green;
            this.ErrorLabel.Location = new System.Drawing.Point(61, 850);
            this.ErrorLabel.Name = "ErrorLabel";
            this.ErrorLabel.Size = new System.Drawing.Size(625, 235);
            this.ErrorLabel.TabIndex = 12;
            this.ErrorLabel.Text = "No Error";
            // 
            // startAgeTextBox
            // 
            this.startAgeTextBox.Location = new System.Drawing.Point(877, 488);
            this.startAgeTextBox.Name = "startAgeTextBox";
            this.startAgeTextBox.Size = new System.Drawing.Size(500, 31);
            this.startAgeTextBox.TabIndex = 13;
            this.startAgeTextBox.Text = "0";
            // 
            // SelectStartAgeLabel
            // 
            this.SelectStartAgeLabel.Location = new System.Drawing.Point(90, 473);
            this.SelectStartAgeLabel.Name = "SelectStartAgeLabel";
            this.SelectStartAgeLabel.Size = new System.Drawing.Size(326, 61);
            this.SelectStartAgeLabel.TabIndex = 14;
            this.SelectStartAgeLabel.Text = "Select Start Age";
            this.SelectStartAgeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // SelectIntervalLabel
            // 
            this.SelectIntervalLabel.Location = new System.Drawing.Point(90, 551);
            this.SelectIntervalLabel.Name = "SelectIntervalLabel";
            this.SelectIntervalLabel.Size = new System.Drawing.Size(326, 63);
            this.SelectIntervalLabel.TabIndex = 15;
            this.SelectIntervalLabel.Text = "Select Interval (days)";
            this.SelectIntervalLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // intervalTextBox
            // 
            this.intervalTextBox.Location = new System.Drawing.Point(877, 551);
            this.intervalTextBox.Name = "intervalTextBox";
            this.intervalTextBox.Size = new System.Drawing.Size(500, 31);
            this.intervalTextBox.TabIndex = 16;
            this.intervalTextBox.Text = "1";
            // 
            // useInterval
            // 
            this.useInterval.AutoSize = true;
            this.useInterval.Location = new System.Drawing.Point(877, 636);
            this.useInterval.Name = "useInterval";
            this.useInterval.Size = new System.Drawing.Size(158, 29);
            this.useInterval.TabIndex = 17;
            this.useInterval.Text = "Use Interval";
            this.useInterval.UseVisualStyleBackColor = true;
            // 
            // OpenCropper
            // 
            this.OpenCropper.Location = new System.Drawing.Point(614, 850);
            this.OpenCropper.Name = "OpenCropper";
            this.OpenCropper.Size = new System.Drawing.Size(244, 72);
            this.OpenCropper.TabIndex = 18;
            this.OpenCropper.Text = "Open Cropper";
            this.OpenCropper.UseVisualStyleBackColor = true;
            this.OpenCropper.Click += new System.EventHandler(this.OpenCropper_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1461, 1143);
            this.Controls.Add(this.OpenCropper);
            this.Controls.Add(this.useInterval);
            this.Controls.Add(this.intervalTextBox);
            this.Controls.Add(this.SelectIntervalLabel);
            this.Controls.Add(this.SelectStartAgeLabel);
            this.Controls.Add(this.startAgeTextBox);
            this.Controls.Add(this.ErrorLabel);
            this.Controls.Add(this.SelectRace);
            this.Controls.Add(this.SelectRaceLabel);
            this.Controls.Add(this.selectGenderLabel);
            this.Controls.Add(this.SelectGender);
            this.Controls.Add(this.SelectDestination);
            this.Controls.Add(this.SelectedDestinationFolder);
            this.Controls.Add(this.SelectedSourceFolder);
            this.Controls.Add(this.SelectSource);
            this.Controls.Add(this.ConvertImages);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button ConvertImages;
        private System.Windows.Forms.Button SelectSource;
        private System.Windows.Forms.Label SelectedSourceFolder;
        private System.Windows.Forms.Label SelectedDestinationFolder;
        private System.Windows.Forms.Button SelectDestination;
        private System.Windows.Forms.ComboBox SelectGender;
        private System.Windows.Forms.Label selectGenderLabel;
        private System.Windows.Forms.Label SelectRaceLabel;
        private System.Windows.Forms.ComboBox SelectRace;
        private System.Windows.Forms.Label ErrorLabel;
        private System.Windows.Forms.TextBox startAgeTextBox;
        private System.Windows.Forms.Label SelectStartAgeLabel;
        private System.Windows.Forms.Label SelectIntervalLabel;
        private System.Windows.Forms.TextBox intervalTextBox;
        private System.Windows.Forms.CheckBox useInterval;
        private System.Windows.Forms.Button OpenCropper;
    }
}

