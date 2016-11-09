using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTT3
{
    public partial class Form1 : Form
    {
        int[,] maze;
        public Form1()
        {
            InitializeComponent();
            dataGridView1.RowCount = 10;
            maze = new int[10,10];
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            MessageBox.Show("Test");
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int row = -1;
            int column = -1;

            row = dataGridView1.CurrentCell.RowIndex;
            column = dataGridView1.CurrentCell.ColumnIndex;

            System.Diagnostics.Debug.WriteLine((column + "," + row + " selected."));

            maze[row,column] = 1;
            dataGridView1.Refresh();
        }

        private void dataGridView1_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
                    if (maze[e.RowIndex,e.ColumnIndex] == 1)
                    {
                        e.CellStyle.BackColor = Color.Black;
                    }
        }
    }
}
