using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameManager : Singleton<GameManager>
{
    [SerializeField]
    private GameObject player;

    [SerializeField]
    private GameObject enemy;

    [SerializeField]
    private GameObject gridObject;

    [SerializeField]
    private GameObject startTitle;

    [SerializeField]
    private GameObject gameingTitle;

    [SerializeField]
    private Button turnButton;

    private GameObject playerObj;
    private int steps;
    public int Steps { get { return steps; } set { steps = value; } }

    public Camera cam;
    Ray ray;
    RaycastHit hit;

    Vector3 mousePos;

    Vector3 dest;
    public Vector3 Dest { get { return dest; } }
    
    private const int rows = 20;
    private const int collums = 30;
    private GameObject[,] grid = new GameObject[rows, collums];
    
    private const int enemyNum = 5;
    private List<GameObject> enemys = new List<GameObject>(enemyNum);

    void Start()
    {
        if(player == null || enemy == null || gridObject==null)
        {
            Debug.LogError("오브젝트가 모두 할당하지 못했습니다.");
        }

        cam = Camera.main;

    }

    void Update()
    {
        mousePos = Input.mousePosition;
        mousePos.z = 100;
        mousePos = cam.ScreenToWorldPoint(mousePos);

        Debug.DrawRay(cam.transform.position, mousePos - cam.transform.position, Color.blue);

        if (Input.GetMouseButtonDown(0))
        {
            ray = cam.ScreenPointToRay(Input.mousePosition);
            if (Physics.Raycast(ray, out hit, Mathf.Infinity))
            {
                Debug.Log(hit.transform.position);
                dest = new Vector3(hit.transform.position.x, 1.5f, hit.transform.position.z);
             
            }
        }

        if (playerObj != null)
        {
            playerObj.GetComponent<Player>().Walkable();
        }
    }


    public void StartScene()
    {
        //UI삭제
        startTitle.SetActive(false);
        gameingTitle.SetActive(true);

        //바닥 생성
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < collums; j++)
            {
                GameObject temp = Instantiate(gridObject, new Vector3(transform.position.x + i, 0,
                    transform.position.z + j), Quaternion.identity);
                temp.transform.SetParent(gameObject.transform);
                grid[i, j] = temp;
            }
        }

        //플레이어 생성
        playerObj = Instantiate(player, new Vector3(transform.position.x, 1.5f, transform.position.z), Quaternion.identity);
        dest = playerObj.transform.position;
        steps = playerObj.GetComponent<Player>().AllowMoveSteps;

        //적 생성
        for (int i = 0; i < enemyNum;i++)
        {
            GameObject temp = Instantiate(enemy, new Vector3(transform.position.x + Random.Range(2,rows), 1.5f,
                transform.position.z + Random.Range(2, collums)), Quaternion.identity);
            enemys.Add(temp);
        }

        ShowMoveableBlock();
    }

    public void ShowMoveableBlock()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < collums; j++)
            {
                grid[i, j].gameObject.GetComponent<Renderer>().material.color = Color.white;
            }
        }

        int x = (int)playerObj.transform.position.x;
        int z = (int)playerObj.transform.position.z;
        GameObject playerPosBlock = grid[x, z];

        for (int i = x - steps; i <= x + steps; i++)
        {
            for (int j = z - steps; j <= z + steps; j++)
            {
                if (i < 0 || i > rows - 1 || j < 0 || j > collums - 1)
                    continue;

                if (i>=-j+x+z-steps && i<=-j + x + z + steps && i<=j+x-z+steps && i>=j+x-z-steps)
                {
                    grid[i, j].gameObject.GetComponent<Renderer>().material.color = Color.green;
                }
            }
        }

    }

    public void EndScene()
    {
        Debug.Log("게임이 종료됩니다");
        Application.Quit();
    }

    public void Turn()
    {
        if (turnButton.GetComponent<Image>().fillAmount == 1)
        {
            turnButton.GetComponent<Image>().fillAmount = 0;
            turnButton.transform.GetChild(0).gameObject.SetActive(false);
            turnButton.transform.GetChild(1).gameObject.SetActive(true);

            StartCoroutine(FillingButton());
            
        }

        else
        {
            Debug.Log("기다리세요...");
        }
    }

    private IEnumerator FillingButton()
    {
        while (true)
        {
            float fillSpeed = 3.5f;
            turnButton.GetComponent<Image>().fillAmount += fillSpeed * Time.deltaTime;
           // Debug.Log(turnButton.GetComponent<Image>().fillAmount);

            if (turnButton.GetComponent<Image>().fillAmount >= 1)
            {
                turnButton.transform.GetChild(0).gameObject.SetActive(true);
                turnButton.transform.GetChild(1).gameObject.SetActive(false);
                break;
            }
            yield return new WaitForSeconds(0.01f);
        }

        steps = playerObj.GetComponent<Player>().AllowMoveSteps;
    }
}
