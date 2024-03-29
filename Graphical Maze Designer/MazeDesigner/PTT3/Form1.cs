﻿using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PTT3
{
    public partial class Form1 : Form
    {
        Maze CurrentMaze;

        public Form1()
        {
            InitializeComponent();
            dataGridViewMaze.RowCount = 10;

            CurrentMaze = new Maze();
            CurrentMaze.scan = new char[10, 10];
            CurrentMaze.solution = new char[10, 10];

            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    CurrentMaze.scan[i, j] = ' ';
                    CurrentMaze.solution[i, j] = ' ';
                }
            }

            saveFileDialog1.DefaultExt = "json";
            saveFileDialog1.FileName = "scan";
        }

        private void dataGridViewMaze_CellFormatting(object sender, DataGridViewCellFormattingEventArgs e)
        {
            if (CurrentMaze.scan[e.RowIndex, e.ColumnIndex] == '#')
            {
                e.CellStyle.BackColor = Color.Black;
            } else if (CurrentMaze.solution[e.RowIndex, e.ColumnIndex] == '$')
            {
                e.CellStyle.BackColor = Color.DarkKhaki;
            } else if(CurrentMaze.solution[e.RowIndex, e.ColumnIndex] == '*')
            {
                e.CellStyle.BackColor = Color.CornflowerBlue;
            }
        }

        private void dataGridViewMaze_CellClick(object sender, DataGridViewCellEventArgs e)
        {
        
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                String path = openFileDialog1.FileName;

                using (StreamReader r = new StreamReader(path))
                {
                    string json = r.ReadToEnd();

                    char[,] deserialized = JsonConvert.DeserializeObject<Maze>(json).scan;
                    char[,] solution = JsonConvert.DeserializeObject<Maze>(json).solution;

                    //CurrentMaze.scan = deserialized;
                    CurrentMaze.solution = solution;
                    CurrentMaze.scan = deserialized;

                    // This line makes sure the cell is updated.
                    dataGridViewMaze.CurrentCell = null;

                    dataGridViewMaze.Refresh();
                }

            }
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            DialogResult result = saveFileDialog1.ShowDialog();

            if(result == DialogResult.OK)
            {
                String path = saveFileDialog1.FileName;

                using (StreamWriter wr = new StreamWriter(path))
                {
                    string json = JsonConvert.SerializeObject(CurrentMaze);

                    wr.Write(json);
                }
            }
        }

        private void dataGridViewMaze_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            int row = e.RowIndex;
            int column = e.ColumnIndex;

            if (e.Button == MouseButtons.Left)
            {
                if (CurrentMaze.scan[row, column] == ' ' || CurrentMaze.scan[row,column] == '\0')
                {
                    CurrentMaze.scan[row, column] = '#';
                }
                else
                {
                    CurrentMaze.scan[row, column] = ' ';
                }
            } else
            {
                CurrentMaze.scan[row, column] = '$';
            }

            // This line makes sure the cell is updated.
            dataGridViewMaze.CurrentCell = null;
        }
    }
}
