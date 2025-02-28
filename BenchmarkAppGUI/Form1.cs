namespace BenchmarkAppGUI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.Load += Form1_Load;
            this.data_benchmark_button.Click += data_benchmark_button_Click;
            this.CPU_benchmark_button.Click += CPU_benchmark_button_Click;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Get the system info from the DLL
            SystemInfo systemInfo = NativeMethods.getSystemInfo();

            // Display the system info in the form
            CPU_name_textbox.Text = NativeMethods.GetCpuModelString(systemInfo);
            CPU_arch_textbox.Text = NativeMethods.GetCpuArchString(systemInfo);
            CPU_physical_cores_textbox.Text = systemInfo.CPU_physical_cores.ToString();
            CPU_logical_cores_textbox.Text = systemInfo.CPU_logical_cores.ToString();
            CPU_clock_textbox.Text = systemInfo.CPU_clock.ToString() + " MHz";
            RAM_size_textbox.Text = systemInfo.RAM_size.ToString() + " MB";
            RAM_load_textbox.Text = systemInfo.RAM_load.ToString() + " %";
            GPU_model_textbox.Text = NativeMethods.GetGpuModelString(systemInfo);

            // Create a timer to update the CPU Clock and RAM Load every 5 seconds
            System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
            timer.Interval = 1000 * 5; // 5 seconds
            timer.Tick += new EventHandler(timer_Tick);
            timer.Start();

            this.ActiveControl = CPU_name_label;

        }

        private void timer_Tick(object sender, EventArgs e)
        {
            //Update the CPU Clock and RAM Load
            int cpuClock = NativeMethods.updateCPUClock();
            int ramLoad = NativeMethods.updateRAMLoad();

            CPU_clock_textbox.Text = cpuClock.ToString() + " MHz";
            RAM_load_textbox.Text = ramLoad.ToString() + " %";
        }

        private void data_benchmark_button_Click(object sender, EventArgs e)
        {
            // Retrieve benchmark data from the DLL
            DataBenchmark dataBenchmark = NativeMethods.getDataBenchmark();

            // Display the benchmark data in the form
            data_benchmark_read_textbox.Text = dataBenchmark.readSpeed.ToString() + " MB/s";
            data_benchmark_write_textbox.Text = dataBenchmark.writeSpeed.ToString() + " MB/s";
        }

        private void CPU_benchmark_button_Click(object sender, EventArgs e)
        {
            // Retrieve the single core CPU benchmark from the DLL
            int singleCoreBenchmark = NativeMethods.getSingleCoreCPUBenchmark();

            // Display the single core CPU benchmark in the form
            CPU_single_core_benchmark_textbox.CustomText = singleCoreBenchmark.ToString();
            if (singleCoreBenchmark > 10000)
            {
                CPU_single_core_benchmark_textbox.Value = 10000;
            }
            else
            {
                CPU_single_core_benchmark_textbox.Value = singleCoreBenchmark;
            }
            CPU_single_core_benchmark_textbox.Value = singleCoreBenchmark;

            // Retrieve the multi core CPU benchmark from the DLL
            int multiCoreBenchmark = NativeMethods.getMultiCoreCPUBenchmark();
            CPU_multi_core_benchmark_textbox.CustomText = multiCoreBenchmark.ToString(); 
            if (multiCoreBenchmark > 10000)
            {
                CPU_multi_core_benchmark_textbox.Value = 10000;
            }
            else
            {
                CPU_multi_core_benchmark_textbox.Value = multiCoreBenchmark;
            }


            // Display the multi core CPU benchmark in the form
            CPU_multi_core_benchmark_textbox.Text = multiCoreBenchmark.ToString();

        }

    }

}

