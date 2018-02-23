/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filler.cs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omykolai <omykolai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 20:31:22 by omykolai          #+#    #+#             */
/*   Updated: 2018/02/18 21:19:34 by omykolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using UnityEngine;
using UnityEngine.UI;

public class	Piece
{
	public char[][]	cells;
	public int		x;
	public int		y;
	public char		player;
	public bool		valid;
}

public class	FillerBehaviour : MonoBehaviour
{
	public char[][]		StartMap;
	public List<Piece>	Pieces;

	public InputField	player1;
	public InputField	player2;
	public InputField	rowCount;
	public InputField	columnCount;

	private bool		displayMessage;
	private string		messageText;

	private void	Start()
	{
        Transform[] allChildren = GetComponentsInChildren<Transform>();
		Text text;

        foreach (Transform child in allChildren)
        {
            if ((text = child.GetComponent<Text>()) != null)
				text.fontSize = (14 * Screen.width) / 1497;
        }
	}

	private void	InitMatrix(ref char[][] mat, string line)
	{
		string[]	info;
		int			n;

		info = line.Split(' ');
		n = Convert.ToInt32(info[1]);
		mat = new char[n][];
	}
	private void	ReadPiece(ref Piece piece, Process p)
	{
		int		i;
		string	line;

		i = 0;
		while (!(line = p.StandardOutput.ReadLine()).Contains("<got"))
		{
			piece.cells[i] = line.ToCharArray();
			++i;
		}
		piece.player = line[6];
		line = line.Substring(11).Split(']')[0];
		piece.x = Convert.ToInt32(line.Split(',')[0]);
		piece.y = Convert.ToInt32(line.Split(',')[1].Substring(1));
		piece.valid = false;
	}
	private void	ReadPiece(Process p, string line)
	{
		Piece piece;

		piece = new Piece();
		InitMatrix(ref piece.cells, line);
		ReadPiece(ref piece, p);
		Pieces.Add(piece);
	}
    private void ConvertOutput(Process p)
    {
        string line;

        ReadMap();
        Pieces = new List<Piece>();
        while ((line = p.StandardOutput.ReadLine()) != null)
        {
            if (String.Compare(line, 0, "Piece", 0, 5, StringComparison.CurrentCulture) == 0)
                ReadPiece(p, line);
        }
    }

    private static string	DirSearch(string sDir, string fName)
    {
        string[] files;
        string f;
        try
        {
            files = System.IO.Directory.GetFiles(sDir, fName);
            if (files != null && files.Length != 0 && files[0] != null)
                return (files[0]);
            foreach (string d in System.IO.Directory.GetDirectories(sDir))
                if ((f = DirSearch(d, fName)) != null)
                    return (f);
            return (null);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            return (null);
        }
    }
    private IEnumerator		MessageCoroutine()
    {
        yield return (new WaitForSeconds(2f));
        displayMessage = false;
    }
    private void			OnGUI()
    {
        if (displayMessage)
        {
            var rect = new Rect(Screen.width / 2 - Screen.width / 16,
                            Screen.height / 2 - Screen.height / 32,
                            Screen.width / 8,
                            Screen.height / 16);
            GUI.Box(rect, messageText);
            StartCoroutine(MessageCoroutine());
        }
    }
    public void		ShowMessage(string text)
    {
        messageText = text;
        displayMessage = true;
    }

    public bool		SetMapParams(out int n, out int m)
    {
		m = 0;
        if (!Int32.TryParse(rowCount.text, out n))
            ShowMessage("Can't render rows count");
        else if (!Int32.TryParse(columnCount.text, out m))
            ShowMessage("Can't render columns count");
        else
			return (true);
		return (false);
    }

	public void		ReadMap()
	{
		int			i;
		string[]	lines;

		lines = System.IO.File.ReadAllLines("map");
        StartMap = new char[lines.Length][];
        for (int j = 0; j < lines.Length; ++j)
            StartMap[j] = new char[lines[0].Length];

		i = 0;
		foreach (var line in lines)
		{
			StartMap[i] = line.ToCharArray();
			++i;
		}
	}
	public void		CreateMap()
	{
		int		n;
		int		m;

		if (SetMapParams(out n, out m))
		{
            StartMap = new char[n][];
            for (int j = 0; j < StartMap.Length; ++j)
                StartMap[j] = new char[m];

            for (int i = 0; i < StartMap.Length; ++i)
                for (int j = 0; j < StartMap[0].Length; ++j)
                    StartMap[i][j] = '.';
		}
	}
	public void		WriteMap()
	{
		if (StartMap != null)
            using (System.IO.StreamWriter file = new System.IO.StreamWriter("map"))
			{
                foreach (char[] line in StartMap)
                    file.WriteLine(line);
			}
	}
	public void		GenerateMap()
	{
		int		n;
		int		m;

        if (SetMapParams(out n, out m))
        {
			Process p = new Process();

			p.StartInfo.UseShellExecute = false;
			p.StartInfo.RedirectStandardOutput = true;
			p.StartInfo.FileName = "gen";
			p.StartInfo.Arguments = String.Format("{0} {1}", rowCount.text, columnCount.text);
			p.Start();
			ConvertOutput(p);
			p.WaitForExit();
		}
	}
	public bool		Execute()
	{
		Process p = new Process();
		string	p1;
		string	p2;
		string	fillerVM;

		p1 = DirSearch("../", player1.text);
        p2 = DirSearch("../", player2.text);
        fillerVM = DirSearch("../", "filler_vm");
		if (p1 == null)
			ShowMessage("Player1 wasn't found.");
        else if (p2 == null)
            ShowMessage("Player2 wasn't found.");
		else if (fillerVM == null)
			ShowMessage("filler_vm executable wasn't found.");
		else
		{
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.FileName = fillerVM;
            p.StartInfo.Arguments = String.Format("-p1 {0} -p2 {1} -f map", p1, p2);
            p.Start();
            ConvertOutput(p);
            p.WaitForExit();
			return (true);	
		}
		return (false);
	}
}
