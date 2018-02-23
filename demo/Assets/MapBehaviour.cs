using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MapBehaviour : MonoBehaviour {

	public GameObject   	cell;
	public GameObject   	line;
	public Material     	player1Material;
	public Material     	player2Material;
	public Material			lineMaterial;
	public GameObject		mapParent;
	public FillerBehaviour  fillerScript;
	public GameBehaviour	gameScript;

	public float        height;
	public float        width;
	public float        cellSize;

	private float       			scale;
	private float					midX;
	private float					midY;
	private List<GameObject>		mapObjects;
	private GameObject				localMapParent;
	private GameObject				cellsParent;

	public IEnumerator	Appear(Stack<Material> materials, float shift)
	{
		for (float f = 0f; f <= 1f; f += shift)
		{
			foreach (var m in materials)
				m.color = new Color(m.color.r, m.color.g, m.color.b, f);
			yield return new WaitForFixedUpdate();
		}
	}
	private GameObject	CreateMapElement(GameObject o, Material material, Stack<Material> materials, Vector3 position, Vector3 scale)
	{
		Material m;

		o = GameObject.Instantiate(o);
		o.transform.parent = localMapParent.transform;
		m = new Material(material);
		o.transform.position = position;
		o.transform.localScale = scale;
		o.GetComponent<Renderer>().material = m;
		m.color = new Color(m.color.r, m.color.g, m.color.b, 0f);
		materials.Push(m);
		return (o);
	}
	private void		CreateLine(float i, float j, float n, float m, Stack<Material> materials)
	{
		float lineWidth;
		Vector3 lineScale;
		Vector3 linePosition;

		lineWidth = (1 - cellSize) * scale;
		linePosition = new Vector3(j * scale - midY, 0, -0.1f);
		lineScale = new Vector3(lineWidth * 0.1f, 1, (n * scale + lineWidth) * 0.1f);
		mapObjects.Add(CreateMapElement(line, lineMaterial, materials, linePosition, lineScale));

		linePosition = new Vector3(0, i * scale - midX, -0.1f);
		lineScale = new Vector3((m * scale + lineWidth) * 0.1f, 1, lineWidth * 0.1f);
		mapObjects.Add(CreateMapElement(line, lineMaterial, materials, linePosition, lineScale));
	}
	public void			CreateCell(float i, float j, float n, float m, Material material, List<GameObject> objList, Stack<Material> materials)
	{
		Vector3		cellScale;
		Vector3		cellPosition;
		GameObject	o;

		cellPosition = new Vector3((j + 0.5f) * scale - midY, (n - i - 0.5f) * scale - midX, -0.1f);
		cellScale = new Vector3(cellSize * scale * 0.1f, 0.01f * scale, cellSize * scale * 0.1f);
		o = CreateMapElement(cell, material, materials, cellPosition, cellScale);
		o.transform.parent = cellsParent.transform;
		objList.Add(o);
	}
    public Material		GetPlayerMaterial(char playerCell)
    {
        return (char.ToUpper(playerCell) == 'O' ? player1Material : player2Material);
    }
    public bool			CheckMap()
    {
		int		n;
		int		m;

        if (fillerScript.StartMap == null)
            return (false);
        if (!fillerScript.SetMapParams(out n, out m))
			return (false);
        if (fillerScript.StartMap.Length != n)
            return (false);
        if (fillerScript.StartMap[0].Length != m)
            return (false);
        return (true);
    }

	public void		SetMap(bool createLines = true)
	{
		Stack<Material> materialsCells;
		Stack<Material> materialsLines;
		float n;
		float m;

		materialsLines = null;
		if (createLines)
		{
			localMapParent = GameObject.Instantiate(mapParent);
			cellsParent = GameObject.Instantiate(mapParent);
			cellsParent.transform.parent = localMapParent.transform;
			mapObjects = new List<GameObject>();
            materialsLines = new Stack<Material>();
		}
        materialsCells = new Stack<Material>();
        gameScript.pieceObjects = new Stack<List<GameObject>>();
        gameScript.resultScript.ResetResult();
        gameScript.player1Score = 0;
        gameScript.player2Score = 0;
		n = fillerScript.StartMap.Length;
		m = fillerScript.StartMap[0].Length;
		scale = Mathf.Min(height / n, width / m);
		midX = (n * scale) / 2;
		midY = (m * scale) / 2;
		for (float i = 0; i <= n; i++)
			for (float j = 0; j <= m; j++)
			{
				if (createLines)
					CreateLine(i, j, n, m, materialsLines);
				if (i != n && j != m)
				{
					if (fillerScript.StartMap[(int)i][(int)j] == 'O')
						CreateCell(i, j, n, m, player1Material, mapObjects, materialsCells);
					else if (fillerScript.StartMap[(int)i][(int)j] == 'X')
						CreateCell(i, j, n, m, player2Material, mapObjects, materialsCells);
				}
			}
		if (createLines)
			StartCoroutine(Appear(materialsLines, 0.007f));
		StartCoroutine(Appear(materialsCells, 0.03f));
	}
	public void		CreateMap()
	{
		if (CheckMap())
			ResetMap();
		else
		{
			gameScript.StopGame(false);
            gameScript.gameStarted = false;
			DestroyMap();
			fillerScript.CreateMap();
			if (fillerScript.StartMap != null)
				SetMap();
		}
	}
	public void		ResetMap()
	{
		if (localMapParent == null)
			CreateMap();
		else
		{
            gameScript.gameStarted = false;
            gameScript.StopGame(false);
            GameObject.Destroy(cellsParent);
            cellsParent = GameObject.Instantiate(mapParent);
            cellsParent.transform.parent = localMapParent.transform;
            for (int i = 0; i < fillerScript.StartMap.Length; ++i)
                for (int j = 0; j < fillerScript.StartMap[0].Length; ++j)
                    fillerScript.StartMap[i][j] = '.';	
		}
	}
	public void		DestroyMap()
	{
        gameScript.StopGame(false);
		if (localMapParent != null)
			GameObject.Destroy(localMapParent);
		fillerScript.StartMap = null;
	}
	public void		GenerateMap()
	{
		bool createM;

        gameScript.StopGame(false);
		createM = CheckMap();
        if (createM)
            ResetMap();
        else
        	DestroyMap();
		fillerScript.GenerateMap();
		fillerScript.ReadMap();
		SetMap(!createM);
	}
}
