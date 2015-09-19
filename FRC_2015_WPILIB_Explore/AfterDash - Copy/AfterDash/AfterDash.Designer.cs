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
            Dundas.Gauges.WinControl.CircularGauge circularGauge1 = new Dundas.Gauges.WinControl.CircularGauge();
            Dundas.Gauges.WinControl.CircularPointer circularPointer1 = new Dundas.Gauges.WinControl.CircularPointer();
            Dundas.Gauges.WinControl.CircularPointer circularPointer2 = new Dundas.Gauges.WinControl.CircularPointer();
            Dundas.Gauges.WinControl.CircularScale circularScale1 = new Dundas.Gauges.WinControl.CircularScale();
            Dundas.Gauges.WinControl.CircularScale circularScale2 = new Dundas.Gauges.WinControl.CircularScale();
            Dundas.Gauges.WinControl.InputValue inputValue1 = new Dundas.Gauges.WinControl.InputValue();
            this.myAMC = new AxAXISMEDIACONTROLLib.AxAxisMediaControl();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label31 = new System.Windows.Forms.Label();
            this.txt_bottomWheelVolts = new System.Windows.Forms.TextBox();
            this.label32 = new System.Windows.Forms.Label();
            this.txt_topWheelVolts = new System.Windows.Forms.TextBox();
            this.txt_Debug = new System.Windows.Forms.TextBox();
            this.topWheelGauge = new Dundas.Gauges.WinControl.GaugeContainer();
            ((System.ComponentModel.ISupportInitialize)(this.myAMC)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.topWheelGauge)).BeginInit();
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
            this.myAMC.Size = new System.Drawing.Size(640, 480);
            this.myAMC.TabIndex = 0;
            this.myAMC.TabStop = false;
            this.myAMC.OnError += new AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnErrorEventHandler(this.myAMC_OnError);
            this.myAMC.OnStatusChange += new AxAXISMEDIACONTROLLib._IAxisMediaControlEvents_OnStatusChangeEventHandler(this.myAMC_OnStatusChange);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label31);
            this.groupBox2.Controls.Add(this.txt_bottomWheelVolts);
            this.groupBox2.Controls.Add(this.label32);
            this.groupBox2.Controls.Add(this.txt_topWheelVolts);
            this.groupBox2.Location = new System.Drawing.Point(1108, 184);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(226, 152);
            this.groupBox2.TabIndex = 41;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Shooter information";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(22, 60);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(77, 13);
            this.label31.TabIndex = 44;
            this.label31.Text = "Bottom Wheel:";
            // 
            // txt_bottomWheelVolts
            // 
            this.txt_bottomWheelVolts.Enabled = false;
            this.txt_bottomWheelVolts.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.txt_bottomWheelVolts.Location = new System.Drawing.Point(105, 57);
            this.txt_bottomWheelVolts.Name = "txt_bottomWheelVolts";
            this.txt_bottomWheelVolts.ReadOnly = true;
            this.txt_bottomWheelVolts.Size = new System.Drawing.Size(100, 20);
            this.txt_bottomWheelVolts.TabIndex = 45;
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(36, 34);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(63, 13);
            this.label32.TabIndex = 42;
            this.label32.Text = "Top Wheel:";
            // 
            // txt_topWheelVolts
            // 
            this.txt_topWheelVolts.Enabled = false;
            this.txt_topWheelVolts.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.txt_topWheelVolts.Location = new System.Drawing.Point(105, 31);
            this.txt_topWheelVolts.Name = "txt_topWheelVolts";
            this.txt_topWheelVolts.ReadOnly = true;
            this.txt_topWheelVolts.Size = new System.Drawing.Size(100, 20);
            this.txt_topWheelVolts.TabIndex = 43;
            // 
            // txt_Debug
            // 
            this.txt_Debug.Enabled = false;
            this.txt_Debug.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.txt_Debug.Location = new System.Drawing.Point(958, 25);
            this.txt_Debug.Name = "txt_Debug";
            this.txt_Debug.ReadOnly = true;
            this.txt_Debug.Size = new System.Drawing.Size(408, 20);
            this.txt_Debug.TabIndex = 46;
            // 
            // topWheelGauge
            // 
            this.topWheelGauge.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.topWheelGauge.BackFrame.FrameShape = Dundas.Gauges.WinControl.BackFrameShape.Rectangular;
            this.topWheelGauge.BackFrame.FrameStyle = Dundas.Gauges.WinControl.BackFrameStyle.None;
            circularGauge1.BackFrame.BackColor = System.Drawing.Color.DarkRed;
            circularGauge1.BackFrame.BackGradientEndColor = System.Drawing.Color.DimGray;
            circularGauge1.BackFrame.FrameColor = System.Drawing.Color.Gold;
            circularGauge1.BackFrame.FrameShape = Dundas.Gauges.WinControl.BackFrameShape.CustomCircular7;
            circularGauge1.BackFrame.FrameStyle = Dundas.Gauges.WinControl.BackFrameStyle.Edged;
            circularGauge1.BackFrame.GlassEffect = Dundas.Gauges.WinControl.GlassEffect.Simple;
            circularGauge1.Location.X = 0F;
            circularGauge1.Location.Y = 0F;
            circularGauge1.Name = "Default";
            circularGauge1.PivotPoint.X = 50F;
            circularGauge1.PivotPoint.Y = 50F;
            circularPointer1.Name = "Feedback";
            circularPointer1.Value = 50D;
            circularPointer2.FillGradientEndColor = System.Drawing.Color.Cyan;
            circularPointer2.Name = "Setpoint";
            circularGauge1.Pointers.Add(circularPointer1);
            circularGauge1.Pointers.Add(circularPointer2);
            circularScale1.FillColor = System.Drawing.Color.Black;
            circularScale1.LabelStyle.TextColor = System.Drawing.Color.White;
            circularScale1.Name = "Default";
            circularScale2.FillColor = System.Drawing.Color.Black;
            circularScale2.LabelStyle.TextColor = System.Drawing.Color.White;
            circularScale2.Maximum = 265D;
            circularScale2.Minimum = 5D;
            circularScale2.Name = "Secondary";
            circularScale2.Radius = 24F;
            circularGauge1.Scales.Add(circularScale1);
            circularGauge1.Scales.Add(circularScale2);
            circularGauge1.Size.Height = 100F;
            circularGauge1.Size.Width = 100F;
            this.topWheelGauge.CircularGauges.Add(circularGauge1);
            this.topWheelGauge.InternalBackgroundPaint = false;
            this.topWheelGauge.Location = new System.Drawing.Point(677, 37);
            this.topWheelGauge.Name = "topWheelGauge";
            this.topWheelGauge.Size = new System.Drawing.Size(400, 400);
            this.topWheelGauge.TabIndex = 42;
            inputValue1.DataMember = "0";
            inputValue1.Name = "Default";
            this.topWheelGauge.Values.Add(inputValue1);
            // 
            // AfterDash
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(1378, 557);
            this.Controls.Add(this.txt_Debug);
            this.Controls.Add(this.topWheelGauge);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.myAMC);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "AfterDash";
            this.Text = "AfterDash";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.AfterDash_FormClosing);
            this.Load += new System.EventHandler(this.AfterDash_Load);
            ((System.ComponentModel.ISupportInitialize)(this.myAMC)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.topWheelGauge)).EndInit();
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
        private GroupBox groupBox2;
        private Label label31;
        private TextBox txt_bottomWheelVolts;
        private Label label32;
        private TextBox txt_topWheelVolts;
        private Dundas.Gauges.WinControl.GaugeContainer topWheelGauge;
        private TextBox txt_Debug;
    }
}

