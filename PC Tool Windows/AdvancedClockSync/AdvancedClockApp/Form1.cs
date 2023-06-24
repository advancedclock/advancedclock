/*
 *
    Send from program 
        Unixtime: UNIX:xxxx|
        reference temp: REF_TEMP:xxxx|

    Recieve Program from uc:
        ERROR:msg|
        ACT_REF_TEMP:xx|
        ACT_TEMP:xx|
        SYNC:1| SYNC:0|
 */

using System.IO.Ports;
using System.Net;
using System.Net.Http.Headers;
using System.Text.Json;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        int RefTemperatureDegree = 0;
        string rxDataBuffer = string.Empty;
        SerialPort _serialPort = null;
        private static UnixDt unixDt = new();


        public Form1()
        {
            InitializeComponent();
            enableUserControl(false);
            loadComPorts();
        }

        #region Button events
        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (_serialPort == null | _serialPort?.IsOpen == false)
                comPortOpen(cbCommPort.SelectedItem?.ToString());
            else
            {
                _serialPort.Dispose();
            }
        }
        private void btnSetRefTemp_Click(object sender, EventArgs e)
        {
            comPortSendData($"REF_TEMP:{RefTemperatureDegree.ToString()}|");
        }
        private void btnRefreshCommPorts_Click(object sender, EventArgs e)
        {
            loadComPorts();
        }
        private void btnClearDbgTxt_Click(object sender, EventArgs e)
        {
            tbDebugRx.Clear();
            tbDebugTx.Clear();
        }
        private async void buttonSync_Click(object sender, EventArgs e)
        {
            await getUnixTimestamp();
            syncUnixDtWithClock();
        }

        #endregion

        #region User input handlers
        private void tbRefTemp_TextChanged(object sender, EventArgs e)
        {
            if (tbRefTemp.Text?.Length > 0)
            {
                if (!Int32.TryParse(tbRefTemp.Text, out RefTemperatureDegree))
                {
                    tbRefTemp.Clear();
                    MessageBox.Show($"Enter numeric value", "Type error",
                                   MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }
        #endregion

        #region User Control settings
        private void enableUserControl(bool enable = false)
        {
            groupBoxRefTemp.Enabled = enable;
            groupBoxStatus.Enabled = enable; ;
            groupBoxSyncDateTime.Enabled = enable;
        }
        #endregion

        #region Com port
        private void loadComPorts()
        {
            string[] ports = SerialPort.GetPortNames();

            cbCommPort.Items.Clear();
            foreach (string port in ports)
            {
                cbCommPort.Items.Add(port);
            }
            cbCommPort.SelectedIndex = 0;
        }
        private void comPortOpen(string portName)
        {
            try
            {
                _serialPort = new SerialPort(portName);

                _serialPort.BaudRate = 9600;
                _serialPort.Parity = Parity.None;
                _serialPort.StopBits = StopBits.One;
                _serialPort.DataBits = 8;
                _serialPort.Handshake = Handshake.None;
                _serialPort.RtsEnable = true;
                _serialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
                _serialPort.Disposed += new EventHandler(comPortDisposed);
                _serialPort.ErrorReceived += comPortDisposed;
                _serialPort.Open();
                _serialPort.WriteTimeout = 1000;
                btnConnect.Text = "Disconnect";
                enableUserControl(_serialPort.IsOpen);
            }
            catch (Exception err)
            {
                MessageBox.Show($"Error opening comm port: {err.Message}", "Error",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void comPortSendData(string data)
        {
            try
            {
                if (_serialPort != null & _serialPort?.IsOpen == true)
                {
                    if (data.Contains('\n') == false)
                        data.Append('\n');

                    _serialPort.WriteLine(data);
                    tbDebugTx.AppendText(data);
                    tbDebugTx.AppendText(Environment.NewLine);
                    tbDebugTx.SelectionStart = tbDebugTx.Text.Length;
                    tbDebugTx.ScrollToCaret();
                }
            }
            catch (Exception err)
            {

                MessageBox.Show($"Error sending com data: {err.Message}", "Send error",
                                   MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }
        private void comPortDisposed(object? sender, EventArgs e)
        {
            btnConnect.Text = "Connect";

            enableUserControl(_serialPort.IsOpen);
        }

        #endregion

        #region Comport data handling
        private void DataReceivedHandler(
                     object sender,
                     SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string data = sp.ReadExisting();
            addDebugTxt(data);

            rxDataBuffer = rxDataBuffer + data;

            parseDataBuffer();
        }

        private void parseDataBuffer()
        {
            while (rxDataBuffer.Contains(':') & rxDataBuffer.Contains('|') & rxDataBuffer.Contains("\r\n"))
            {
                {
                    string data = rxDataBuffer.Substring(0, rxDataBuffer.IndexOf("\r\n"));
                    string cmd = getCmdAsString(data);
                    string val = getDataValAsString(data);
                    rxDataBuffer = rxDataBuffer.Remove(0, rxDataBuffer.IndexOf("\r\n") + 2);

                    switch (cmd)
                    {
                        case "ERROR":
                            {
                                lblError.Invoke((MethodInvoker)delegate
                                {
                                    lblError.Text = val;
                                });
                                break;
                            }
                        case "ACT_REF_TEMP":
                            {
                                lblRefTemp.Invoke((MethodInvoker)delegate
                                {
                                    lblRefTemp.Text = string.Format("{0}°C", val);
                                });
                                break;
                            }
                        case "ACT_TEMP":
                            {
                                lblActTemp.Invoke((MethodInvoker)delegate
                                {
                                    lblActTemp.Text = string.Format("{0}°C", val);
                                });
                                break;
                            }
                        case "SYNC":
                            {
                                if (val == "1")
                                {
                                    lblSyncStat.Invoke((MethodInvoker)delegate
                                    {
                                        lblSyncStat.Text = "synchronised";
                                        lblSyncStat.ForeColor = Color.Green;
                                    });
                                }
                                else if (val == "0")
                                {
                                    lblSyncStat.Invoke((MethodInvoker)delegate
                                    {
                                        lblSyncStat.Text = "Not synchronised";
                                        lblSyncStat.ForeColor = Color.Red;
                                    });
                                }

                                break;
                            }
                        default:
                            break;
                    }
                }
            }


        }

        string getCmdAsString(String data)
        {
            if (data.Contains(':'))
                return data.Substring(0, data.IndexOf(':'));
            else
                return string.Empty;
        }

        string getDataValAsString(String data)
        {
            if (data.Contains(':') & data.Contains('|'))
            {
                int length = ((data.IndexOf('|') - data.IndexOf(':')) - 1);
                return data.Substring(data.IndexOf(':') + 1, length);
            }
            else
                return string.Empty;
        }
        #endregion

        #region Unix time stamp
        private async Task getUnixTimestamp()
        {
            try
            {
                HttpClient client = new HttpClient();
                client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

                using (HttpResponseMessage response = await client.GetAsync(new Uri("http://worldtimeapi.org/api/timezone/Europe/Amsterdam")))
                {
                    using (HttpContent content = response.Content)
                    {

                        var readFromJsonAsync = content.ReadAsStringAsync().Result;
                        unixDt = JsonSerializer.Deserialize<UnixDt>(readFromJsonAsync);
                        unixDt.unixtime = unixDt.unixtime + unixDt.dst_offset + unixDt.raw_offset; //timezone

                    }

                }
            }
            catch
            {
                MessageBox.Show("getUnixTimestamp failed");
            }
        }
        private void syncUnixDtWithClock()
        {

            lblTime.Invoke((MethodInvoker)delegate
            {
                lblTime.Text = unixDt.datetime.TimeOfDay.ToString("hh\\:mm\\:ss");
            });

            lblDate.Invoke((MethodInvoker)delegate
            {
                lblDate.Text = unixDt.datetime.Date.ToString("dd/MM/yyyy");
            });

            lblUnix.Invoke((MethodInvoker)delegate
            {
                lblUnix.Text = unixDt.unixtime.ToString();
            });

            comPortSendData($"UNIX:{unixDt.unixtime}|");
        }
        #endregion

        void addDebugTxt(string txt)
        {
            tbDebugRx.Invoke((MethodInvoker)delegate
            {
                //tbDebugRx.Text = tbDebugRx.Text + '\n' + txt;
                tbDebugRx.AppendText(txt);
            });
        }

        private void Program_Closing(object sender, FormClosingEventArgs e)
        {
            if (_serialPort != null)
            {
                _serialPort.Dispose();
            }
        }

    }
}