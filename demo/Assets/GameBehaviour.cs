using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameBehaviour : MonoBehaviour 
{
	public MapBehaviour		mapScript;
	public FillerBehaviour	fillerScript;
	public ResultBehaviour	resultScript;

    public Stack<List<GameObject>> pieceObjects;
	private bool	continueAddPiece;
	public bool		gameStarted;
	public int		player1Score;
	public int		player2Score;

	private void	AddScore(char player, int val = 1)
	{
		if (char.ToUpper(player) == 'O')
			player1Score += val;
        else if (char.ToUpper(player) == 'X')
            player2Score += val;
        resultScript.UpdateResult(player1Score, player2Score, fillerScript.Pieces.Count);
	}
    private int 	AddPieceCell(float i, float j, char playerCell, Stack<Material> materials, List<GameObject> pieceList)
    {
        float n;
        float m;

        n = fillerScript.StartMap.Length;
        m = fillerScript.StartMap[0].Length;
        if (i >= 0f && j >= 0f && i < n && j < m)
        {
            if (fillerScript.StartMap[(int)i][(int)j] == '.')
            {
                mapScript.CreateCell(i, j, n, m, mapScript.GetPlayerMaterial(playerCell), pieceList, materials);
                fillerScript.StartMap[(int)i][(int)j] = playerCell;
                return (0);
            }
            if (char.ToUpper(fillerScript.StartMap[(int)i][(int)j]) == playerCell)
                return (1);
        }
        return (2);
    }
    public bool 	AddPiece()
    {
        Stack<Material> materials;
        List<GameObject> pieceList;
        int pieceI;
        int intersectionCount;
        float n;
        float m;

        pieceI = pieceObjects.Count;
        materials = new Stack<Material>();
        pieceList = new List<GameObject>();
        intersectionCount = 0;
        if (pieceI >= fillerScript.Pieces.Count)
            return (false);
        n = fillerScript.Pieces[pieceI].cells.Length;
        m = fillerScript.Pieces[pieceI].cells[0].Length;
		AddScore(fillerScript.Pieces[pieceI].player);
        for (float i = 0; i < n; i++)
            for (float j = 0; j < m; j++)
                if (fillerScript.Pieces[pieceI].cells[(int)i][(int)j] == '*')
                {
                    intersectionCount += AddPieceCell(i + fillerScript.Pieces[pieceI].x, j + fillerScript.Pieces[pieceI].y, fillerScript.Pieces[pieceI].player, materials, pieceList);
                }
        pieceObjects.Push(pieceList);
        if (intersectionCount == 1 || fillerScript.Pieces[pieceI].valid)
            StartCoroutine(mapScript.Appear(materials, 0.05f));
        return (true);
    }

	private IEnumerator	ExecuteGame()
	{
		while (AddPiece() && continueAddPiece)
			yield return new WaitForFixedUpdate();
	}
	private bool	InitGame()
	{
		if (!gameStarted)
		{
            if (!mapScript.CheckMap())
                mapScript.GenerateMap();
			fillerScript.WriteMap();
			if (!fillerScript.Execute())
				return (false);
			gameStarted = true;
		}
        continueAddPiece = true;
		return (true);
	}
	public void		StartGame()
	{
		if (pieceObjects == null || pieceObjects.Count == 0 || pieceObjects.Count == fillerScript.Pieces.Count)
			StopGame();
		if (InitGame())
			StartCoroutine(ExecuteGame());
	}
	public void		PauseGame()
	{
		continueAddPiece = false;
	}
	public void		StopGame(bool reset = true)
	{
		StopAllCoroutines();
		if (reset)
		{
            mapScript.ResetMap();
			fillerScript.ReadMap();
            mapScript.SetMap(false);
		}
	}

	public void		NextMove()
	{
        if (InitGame())
			AddPiece();
	}

	public void		PrevMove()
	{
		int pieceI;
		int n;
		int m;

		foreach (var p in pieceObjects.Pop())
			GameObject.Destroy(p);
		pieceI = pieceObjects.Count;
        n = fillerScript.Pieces[pieceI].cells.Length;
        m = fillerScript.Pieces[pieceI].cells[0].Length;
        fillerScript.Pieces[pieceI].valid = true;
		AddScore(fillerScript.Pieces[pieceI].player, -1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (fillerScript.Pieces[pieceI].cells[i][j] == '*')
                {
                    fillerScript.StartMap[i + fillerScript.Pieces[pieceI].x][j + fillerScript.Pieces[pieceI].y] = '.';
                }
	}
}
