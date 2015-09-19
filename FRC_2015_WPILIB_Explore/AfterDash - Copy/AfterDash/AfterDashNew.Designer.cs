using System.Threading;
using System.IO;
using System.Windows.Forms;
namespace AfterDash
{
    partial class AfterDash
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(AfterDash));
            this.myAMC = new AxAXISMEDIACONTROLLib.AxAxisMediaControl();
            this.POTSetpoint = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SonicFeet = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.myAMC)).BeginInit();
            this.SuspendLayout();
            // 
            // myAMC
            // 
            this.myAMC.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.myAMC.Enabled = true;
            this.myAMC.Location = new System.Drawing.Point(12, 12);
            this.myAMC.Name = "myAMC";
            this.myAMC.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("myAMC.OcxState")));
            this.myAMC.Size = new System.Drawing.Size(368, 312);
            this.myAMC.TabIndex = 0;
            this.myAMC.TabStop = false;
            this.myAMC.OnError += new AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnErrorEventHandler(this.myAMC_OnError);
            this.myAMC.OnStatusChange += new AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnStatusChangeEventHandler(this.myAMC_OnStatusChange);
            // 
            // POTSetpoint
            // 
            this.POTSetpoint.Location = new System.Drawing.Point(429, 95);
            this.POTSetpoint.Name = "POTSetpoint";
            this.POTSetpoint.Size = new System.Drawing.Size(100, 96);
            this.POTSetpoint.TabIndex = 2;
            this.POTSetpoint.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Black;
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(426, 79);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "POT SETPOINT";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Black;
            this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label2.Location = new System.Drawing.Point(570, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(118, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "SONIC SENSOR FEET";
            // 
            // SonicFeet
            // 
            this.SonicFeet.Location = new System.Drawing.Point(573, 95);
            this.SonicFeet.Name = "SonicFeet";
            this.SonicFeet.Size = new System.Drawing.Size(100, 96);
            this.SonicFeet.TabIndex = 4;
            this.SonicFeet.Text = "";
            // 
            // AfterDash
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(1036, 557);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.SonicFeet);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.POTSetpoint);
            this.Controls.Add(this.myAMC);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "AfterDash";
            this.Text = "AfterDash";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AfterDash_FormClosing);
            this.Load += new System.EventHandler(this.AfterDash_Load);
            ((System.ComponentModel.ISupportInitialize)(this.myAMC)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        
        private void myAMC_OnError(object sender, AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnErrorEvent e)
        {
            Thread.Sleep(1);
            myAMC.StopRecordMedia();
            myAMC.Play();
        }
        private void myAMC_OnStatusChange(object sender, AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnStatusChangeEvent e)
        {
            //MessageBox.Show("Status: " + e.theNewStatus);
            if (e.theNewStatus == 1027)
            {

                int i = 1;
                while (File.Exists("Recordings/AftershockRecord_" + i + ".asf")) { i++; }
                myAMC.StartRecordMedia("Recordings/AftershockRecord_" + i + ".asf", 8, "");
            }

        }
        public AxAXISMEDIACONTROLLib.AxAxisMediaControl myAMC;
        private RichTextBox POTSetpoint;
        private Label label1;
        private Label label2;
        private RichTextBox SonicFeet;
    }
}

