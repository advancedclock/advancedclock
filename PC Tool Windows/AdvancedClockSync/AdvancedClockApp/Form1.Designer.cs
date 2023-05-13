namespace WinFormsApp1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.tbDebugRx = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnRefreshCommPorts = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.btnConnect = new System.Windows.Forms.Button();
            this.cbCommPort = new System.Windows.Forms.ComboBox();
            this.groupBoxRefTemp = new System.Windows.Forms.GroupBox();
            this.btnSetRefTemp = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tbRefTemp = new System.Windows.Forms.TextBox();
            this.groupBoxStatus = new System.Windows.Forms.GroupBox();
            this.lblRefTemp = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.lblError = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lblActTemp = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblSyncStat = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.helpProvider1 = new System.Windows.Forms.HelpProvider();
            this.groupBoxSyncDateTime = new System.Windows.Forms.GroupBox();
            this.lblUnix = new System.Windows.Forms.Label();
            this.lblDate = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lblTime = new System.Windows.Forms.Label();
            this.btnSync = new System.Windows.Forms.Button();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.tbDebugTx = new System.Windows.Forms.TextBox();
            this.btnClearDbgTxt = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBoxRefTemp.SuspendLayout();
            this.groupBoxStatus.SuspendLayout();
            this.groupBoxSyncDateTime.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbDebugRx
            // 
            this.tbDebugRx.Location = new System.Drawing.Point(6, 22);
            this.tbDebugRx.Multiline = true;
            this.tbDebugRx.Name = "tbDebugRx";
            this.tbDebugRx.ReadOnly = true;
            this.tbDebugRx.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbDebugRx.Size = new System.Drawing.Size(373, 279);
            this.tbDebugRx.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnRefreshCommPorts);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.btnConnect);
            this.groupBox1.Controls.Add(this.cbCommPort);
            this.groupBox1.Location = new System.Drawing.Point(15, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(209, 100);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Connection";
            // 
            // btnRefreshCommPorts
            // 
            this.btnRefreshCommPorts.Location = new System.Drawing.Point(47, 70);
            this.btnRefreshCommPorts.Name = "btnRefreshCommPorts";
            this.btnRefreshCommPorts.Size = new System.Drawing.Size(75, 23);
            this.btnRefreshCommPorts.TabIndex = 4;
            this.btnRefreshCommPorts.Text = "Refresh";
            this.btnRefreshCommPorts.UseVisualStyleBackColor = true;
            this.btnRefreshCommPorts.Click += new System.EventHandler(this.btnRefreshCommPorts_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 21);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 15);
            this.label2.TabIndex = 3;
            this.label2.Text = "Com-port";
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(128, 70);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(75, 23);
            this.btnConnect.TabIndex = 1;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // cbCommPort
            // 
            this.cbCommPort.FormattingEnabled = true;
            this.cbCommPort.Location = new System.Drawing.Point(82, 18);
            this.cbCommPort.Name = "cbCommPort";
            this.cbCommPort.Size = new System.Drawing.Size(121, 23);
            this.cbCommPort.TabIndex = 0;
            // 
            // groupBoxRefTemp
            // 
            this.groupBoxRefTemp.Controls.Add(this.btnSetRefTemp);
            this.groupBoxRefTemp.Controls.Add(this.label1);
            this.groupBoxRefTemp.Controls.Add(this.tbRefTemp);
            this.groupBoxRefTemp.Location = new System.Drawing.Point(425, 4);
            this.groupBoxRefTemp.Name = "groupBoxRefTemp";
            this.groupBoxRefTemp.Size = new System.Drawing.Size(175, 100);
            this.groupBoxRefTemp.TabIndex = 3;
            this.groupBoxRefTemp.TabStop = false;
            this.groupBoxRefTemp.Text = "Temperature";
            // 
            // btnSetRefTemp
            // 
            this.btnSetRefTemp.Location = new System.Drawing.Point(94, 70);
            this.btnSetRefTemp.Name = "btnSetRefTemp";
            this.btnSetRefTemp.Size = new System.Drawing.Size(75, 23);
            this.btnSetRefTemp.TabIndex = 3;
            this.btnSetRefTemp.Text = "Set";
            this.btnSetRefTemp.UseVisualStyleBackColor = true;
            this.btnSetRefTemp.Click += new System.EventHandler(this.btnSetRefTemp_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 15);
            this.label1.TabIndex = 2;
            this.label1.Text = "Ref. temp.";
            // 
            // tbRefTemp
            // 
            this.tbRefTemp.Location = new System.Drawing.Point(79, 18);
            this.tbRefTemp.Name = "tbRefTemp";
            this.tbRefTemp.Size = new System.Drawing.Size(75, 23);
            this.tbRefTemp.TabIndex = 1;
            this.tbRefTemp.TextChanged += new System.EventHandler(this.tbRefTemp_TextChanged);
            // 
            // groupBoxStatus
            // 
            this.groupBoxStatus.Controls.Add(this.lblRefTemp);
            this.groupBoxStatus.Controls.Add(this.label11);
            this.groupBoxStatus.Controls.Add(this.lblError);
            this.groupBoxStatus.Controls.Add(this.label7);
            this.groupBoxStatus.Controls.Add(this.lblActTemp);
            this.groupBoxStatus.Controls.Add(this.label5);
            this.groupBoxStatus.Controls.Add(this.lblSyncStat);
            this.groupBoxStatus.Controls.Add(this.label3);
            this.groupBoxStatus.Location = new System.Drawing.Point(613, 4);
            this.groupBoxStatus.Name = "groupBoxStatus";
            this.groupBoxStatus.Size = new System.Drawing.Size(175, 100);
            this.groupBoxStatus.TabIndex = 4;
            this.groupBoxStatus.TabStop = false;
            this.groupBoxStatus.Text = "Status";
            // 
            // lblRefTemp
            // 
            this.lblRefTemp.AutoSize = true;
            this.lblRefTemp.Location = new System.Drawing.Point(62, 38);
            this.lblRefTemp.Name = "lblRefTemp";
            this.lblRefTemp.Size = new System.Drawing.Size(29, 15);
            this.lblRefTemp.TabIndex = 10;
            this.lblRefTemp.Text = "0 °C";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(9, 38);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(55, 15);
            this.label11.TabIndex = 9;
            this.label11.Text = "Ref temp";
            // 
            // lblError
            // 
            this.lblError.AutoSize = true;
            this.lblError.ForeColor = System.Drawing.Color.Black;
            this.lblError.Location = new System.Drawing.Point(62, 70);
            this.lblError.Name = "lblError";
            this.lblError.Size = new System.Drawing.Size(36, 15);
            this.lblError.TabIndex = 8;
            this.lblError.Text = "None";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 70);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(32, 15);
            this.label7.TabIndex = 7;
            this.label7.Text = "Error";
            // 
            // lblActTemp
            // 
            this.lblActTemp.AutoSize = true;
            this.lblActTemp.Location = new System.Drawing.Point(62, 21);
            this.lblActTemp.Name = "lblActTemp";
            this.lblActTemp.Size = new System.Drawing.Size(29, 15);
            this.lblActTemp.TabIndex = 6;
            this.lblActTemp.Text = "0 °C";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 54);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(33, 15);
            this.label5.TabIndex = 5;
            this.label5.Text = "Time";
            // 
            // lblSyncStat
            // 
            this.lblSyncStat.AutoSize = true;
            this.lblSyncStat.ForeColor = System.Drawing.Color.Red;
            this.lblSyncStat.Location = new System.Drawing.Point(62, 54);
            this.lblSyncStat.Name = "lblSyncStat";
            this.lblSyncStat.Size = new System.Drawing.Size(100, 15);
            this.lblSyncStat.TabIndex = 4;
            this.lblSyncStat.Text = "Not synchronised";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 15);
            this.label3.TabIndex = 2;
            this.label3.Text = "Temp";
            // 
            // groupBoxSyncDateTime
            // 
            this.groupBoxSyncDateTime.Controls.Add(this.lblUnix);
            this.groupBoxSyncDateTime.Controls.Add(this.lblDate);
            this.groupBoxSyncDateTime.Controls.Add(this.label8);
            this.groupBoxSyncDateTime.Controls.Add(this.label6);
            this.groupBoxSyncDateTime.Controls.Add(this.label4);
            this.groupBoxSyncDateTime.Controls.Add(this.lblTime);
            this.groupBoxSyncDateTime.Controls.Add(this.btnSync);
            this.groupBoxSyncDateTime.Location = new System.Drawing.Point(237, 4);
            this.groupBoxSyncDateTime.Name = "groupBoxSyncDateTime";
            this.groupBoxSyncDateTime.Size = new System.Drawing.Size(175, 100);
            this.groupBoxSyncDateTime.TabIndex = 4;
            this.groupBoxSyncDateTime.TabStop = false;
            this.groupBoxSyncDateTime.Text = "Date time";
            // 
            // lblUnix
            // 
            this.lblUnix.AutoSize = true;
            this.lblUnix.Location = new System.Drawing.Point(94, 53);
            this.lblUnix.Name = "lblUnix";
            this.lblUnix.Size = new System.Drawing.Size(0, 15);
            this.lblUnix.TabIndex = 9;
            // 
            // lblDate
            // 
            this.lblDate.AutoSize = true;
            this.lblDate.Location = new System.Drawing.Point(94, 38);
            this.lblDate.Name = "lblDate";
            this.lblDate.Size = new System.Drawing.Size(0, 15);
            this.lblDate.TabIndex = 8;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(10, 38);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(31, 15);
            this.label8.TabIndex = 7;
            this.label8.Text = "Date";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(10, 54);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(57, 15);
            this.label6.TabIndex = 6;
            this.label6.Text = "UnixTime";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(10, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(33, 15);
            this.label4.TabIndex = 5;
            this.label4.Text = "Time";
            // 
            // lblTime
            // 
            this.lblTime.AutoSize = true;
            this.lblTime.Location = new System.Drawing.Point(94, 22);
            this.lblTime.Name = "lblTime";
            this.lblTime.Size = new System.Drawing.Size(0, 15);
            this.lblTime.TabIndex = 4;
            // 
            // btnSync
            // 
            this.btnSync.Location = new System.Drawing.Point(94, 70);
            this.btnSync.Name = "btnSync";
            this.btnSync.Size = new System.Drawing.Size(75, 23);
            this.btnSync.TabIndex = 3;
            this.btnSync.Text = "Sync";
            this.btnSync.UseVisualStyleBackColor = true;
            this.btnSync.Click += new System.EventHandler(this.buttonSync_Click);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.label10);
            this.groupBox5.Controls.Add(this.label9);
            this.groupBox5.Controls.Add(this.tbDebugTx);
            this.groupBox5.Controls.Add(this.btnClearDbgTxt);
            this.groupBox5.Controls.Add(this.tbDebugRx);
            this.groupBox5.Location = new System.Drawing.Point(15, 110);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(773, 337);
            this.groupBox5.TabIndex = 5;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Debug info";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(397, 13);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(18, 15);
            this.label10.TabIndex = 8;
            this.label10.Text = "Tx";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(8, 13);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(20, 15);
            this.label9.TabIndex = 7;
            this.label9.Text = "Rx";
            // 
            // tbDebugTx
            // 
            this.tbDebugTx.Location = new System.Drawing.Point(397, 22);
            this.tbDebugTx.Multiline = true;
            this.tbDebugTx.Name = "tbDebugTx";
            this.tbDebugTx.ReadOnly = true;
            this.tbDebugTx.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbDebugTx.Size = new System.Drawing.Size(370, 279);
            this.tbDebugTx.TabIndex = 6;
            // 
            // btnClearDbgTxt
            // 
            this.btnClearDbgTxt.Location = new System.Drawing.Point(692, 302);
            this.btnClearDbgTxt.Name = "btnClearDbgTxt";
            this.btnClearDbgTxt.Size = new System.Drawing.Size(75, 32);
            this.btnClearDbgTxt.TabIndex = 5;
            this.btnClearDbgTxt.Text = "Clear";
            this.btnClearDbgTxt.UseVisualStyleBackColor = true;
            this.btnClearDbgTxt.Click += new System.EventHandler(this.btnClearDbgTxt_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBoxSyncDateTime);
            this.Controls.Add(this.groupBoxRefTemp);
            this.Controls.Add(this.groupBoxStatus);
            this.Controls.Add(this.groupBox1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MdiChildrenMinimizedAnchorBottom = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.Text = "Advanced clock";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Program_Closing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBoxRefTemp.ResumeLayout(false);
            this.groupBoxRefTemp.PerformLayout();
            this.groupBoxStatus.ResumeLayout(false);
            this.groupBoxStatus.PerformLayout();
            this.groupBoxSyncDateTime.ResumeLayout(false);
            this.groupBoxSyncDateTime.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private TextBox tbDebugRx;
        private GroupBox groupBox1;
        private Label label2;
        private Button btnConnect;
        private ComboBox cbCommPort;
        private GroupBox groupBoxRefTemp;
        private Label label1;
        private TextBox tbRefTemp;
        private Button btnSetRefTemp;
        private GroupBox groupBoxStatus;
        private Label label3;
        private HelpProvider helpProvider1;
        private Label lblError;
        private Label label7;
        private Label lblActTemp;
        private Label label5;
        private Label lblSyncStat;
        private GroupBox groupBoxSyncDateTime;
        private Button btnSync;
        private Label lblTime;
        private GroupBox groupBox5;
        private Button btnRefreshCommPorts;
        private Button btnClearDbgTxt;
        private TextBox tbDebugTx;
        private Label label10;
        private Label label9;
        private Label lblRefTemp;
        private Label label11;
        private Label label8;
        private Label label6;
        private Label label4;
        private Label lblUnix;
        private Label lblDate;
    }
}