using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace WinFormsApp1
{
    public class UnixDt
    { 
        public string abbreviation { get; set; }
        public string client_ip { get; set; }
        public DateTime datetime { get; set; }
        public int day_of_week { get; set; }
        public int day_of_year { get; set; }
        public bool dst { get; set; }
        public object dst_from { get; set; }
        public int dst_offset { get; set; }
        public object dst_until { get; set; }
        public int raw_offset { get; set; }
        public string timezone { get; set; }
        public DateTime utc_datetime { get; set; }
        public string utc_offset { get; set; }
        public int week_number { get; set; }

        private long _unixtime;
        public long unixtime
        {
            get { return _unixtime; }
            set
            {
                if (value != null)
                { 
                    _unixtime = value;

                }

            }
        }

    }
}
