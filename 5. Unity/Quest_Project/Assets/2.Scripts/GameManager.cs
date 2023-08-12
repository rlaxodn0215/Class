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
    private GameObject item;

    //UI
    [SerializeField]
    private GameObject startTitle;

    [SerializeField]
    private GameObject gameingTitle;

    [SerializeField]
    private Button turnButton;

    [SerializeField]
    private Button potionButton;

    [SerializeField]
    private Button weaponButton;

    private GameObject playerObj;
    public GameObject PlayerObj { get { return playerObj; }set { playerObj = value; } }
    private int steps;
    public int Steps { get { return steps; } set { steps = value; } }

    private bool gameStart = false;
    private bool turnOver = true;

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
    public List<GameObject> enemys = new List<GameObject>(enemyNum);

    private const int itemNum = 3;
    public List<GameObject> items = new List<GameObject>(itemNum);

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
            if (Physics.Raycast(ray, out hit, Mathf.Infinity) && turnOver)
            {
                Debug.Log(hit.transform.position);
                dest = new Vector3(hit.transform.position.x, 1.5f, hit.transform.position.z);

                if (playerObj != null && gameStart) PlayerWalkable();
                if (steps == 0)
                {
                    Turn();
                    steps = playerObj.GetComponent<Player>().AllowMoveSteps;
                    ShowMoveableBlock();
                }
            }
        }

    }

    public void PlayerWalkable()
    {
        Vector3 diff = dest - playerObj.transform.position;
        int count = (int)(Mathf.Abs(diff.x) + Mathf.Abs(diff.z));

        if (count <= playerObj.GetComponent<Player>().AllowMoveSteps && steps > 0)
        {
            if (hit.transform.gameObject.tag == "Enemy")
            {
                if (playerObj.GetComponent<Player>().AttackOther(count))
                {
                    hit.transform.GetComponent<Enemy>().hp -= playerObj.GetComponent<Player>().Attack;
                    Debug.LogWarning("적 체력 감소, 적 체력 : " + hit.transform.GetComponent<Enemy>().hp);
                    if (hit.transform.GetComponent<Enemy>().hp == 0) Destroy(hit.transform.gameObject);
                    Turn();

                }
            }

            else if (hit.transform.gameObject.tag == "Item")
            {
                int randNUm = Random.Range(0,2);
                Debug.LogWarning("아이템 습득 : " + hit.transform.GetComponent<Item>().ItemMenu(randNUm));
                if(randNUm==0)
                {
                    playerObj.GetComponent<Player>().hasArrow = true;
                    
                }

                else
                {
                    playerObj.GetComponent<Player>().HP_potionNum++;
                }
                Destroy(hit.transform.gameObject);
                Turn();
            }

            else
            {
                steps -= count;
                StartCoroutine(PlayerMove(dest));
                ShowMoveableBlock();
            }
        }

    }

    public IEnumerator PlayerMove(Vector3 dest)
    {
        while (dest !=playerObj.transform.position)
        {
            playerObj.GetComponent<Player>().Move();
            PlayerObj.GetComponent<Player>().MoveFinish = false;
            yield return null;
        }

        if(dest == playerObj.transform.position)
        {
            PlayerObj.GetComponent<Player>().MoveFinish = true;
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

        //아이템 생성
        for (int i = 0; i < itemNum; i++)
        {
            GameObject temp = Instantiate(item, new Vector3(transform.position.x + Random.Range(2, rows), 1.5f,
                transform.position.z + Random.Range(2, collums)), Quaternion.identity);
            items.Add(temp);
        }

        ShowMoveableBlock();
        gameStart = true;
    }

    private void ShowMoveableBlock()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < collums; j++)
            {
                grid[i, j].gameObject.GetComponent<Renderer>().material.color = Color.white;
            }
        }

        if (steps == 0) return;

        //int x = (int)playerObj.transform.position.x;
        //int z = (int)playerObj.transform.position.z;
        int x = (int)dest.x;
        int z = (int)dest.z;

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

    public void Turn()
    {
        turnOver = false;
       turnButton.transform.GetChild(0).gameObject.SetActive(false);
       turnButton.transform.GetChild(1).gameObject.SetActive(true);
       steps = playerObj.GetComponent<Player>().AllowMoveSteps;
        ShowMoveableBlock();
        StartCoroutine(EnemyMove());
    }

    public IEnumerator EnemyMove()
    {
        foreach (GameObject obj in enemys)
        {
            if (obj == null) continue;

            obj.GetComponent<Enemy>().Destin = EnemyDest(obj);

            while (EnemyMoveable(obj.GetComponent<Enemy>().Destin, obj))
            {
                obj.GetComponent<Enemy>().Move();
                yield return null;
            }

        }

        turnButton.transform.GetChild(0).gameObject.SetActive(true);
        turnButton.transform.GetChild(1).gameObject.SetActive(false);
        turnOver = true;
    }

    public bool EnemyMoveable(Vector3 dest, GameObject enemy)
    {
        if (Vector3.Magnitude(dest - enemy.transform.position) > 0)
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    public void EndScene()
    {
        Debug.Log("게임이 종료됩니다");
        Application.Quit();
    }

    public Vector3 EnemyDest(GameObject enemy)
    {
        Vector3 diff = GameManager.Instance.Dest - enemy.transform.position;
        Vector3 min = new Vector3(0, 0, 100);

        for (int i = -enemy.GetComponent<Enemy>().AllowSteps; i <= enemy.GetComponent<Enemy>().AllowSteps; i++)
        {
            for (int j = -enemy.GetComponent<Enemy>().AllowSteps; j <= enemy.GetComponent<Enemy>().AllowSteps; j++)
            {
                if (transform.position.x + i >= 0 && transform.position.x + i < 20 &&
                    transform.position.z + i >= 0 && transform.position.z + i < 30)
                {
                    if (Mathf.Abs(i) + Mathf.Abs(j) <= enemy.GetComponent<Enemy>().AllowSteps && CheckNearbyObj(enemy, i, j))
                    {
                        Vector3 temp = new Vector3(i, 0, j);
                        Vector3 temp1 = diff - temp;
                        min = (Vector3.Magnitude(diff - min) < Vector3.Magnitude(temp1)) ? min : temp;

                    }
                }

            }
        }

        return (min + enemy.transform.position);
    }

    private bool CheckNearbyObj(GameObject enemy, int i, int j)
    {
        Vector3 point = enemy.transform.position + new Vector3(i, 0, j);

        foreach (GameObject obj in enemys)
        {
            if (obj == null) continue;

            if (obj.transform.position == point)
            {
                if(enemy != obj)
                return false;
            }

            if(Dest == point)
            {
                enemy.GetComponent<Enemy>().AttackOther(0);
                if (playerObj.GetComponent<Player>().HP == 0) Debug.LogError("플레이어 사망");
                return false;
            }
        }

        foreach(GameObject obj in items)
        {
            if (obj == null) continue;

            if (obj.transform.position == point)
            {
                    return false;
            }
        }

        return true;

    }

    public void Potion()
    {
        if(playerObj.GetComponent<Player>().HP_potionNum>0)
        {
            Debug.LogWarning("플레이어 체력 증가, 플레이어 체력 : " + playerObj.GetComponent<Player>().HP);
            playerObj.GetComponent<Player>().HP += 10;
            playerObj.GetComponent<Player>().HP_potionNum--;
        }

        else
        {
            Debug.LogWarning("체력 포션이 없습니다.");
        }
    }

    public void Weapon()
    {
        if(playerObj.GetComponent<Player>().hasArrow)
        {
            if(weaponButton.transform.GetChild(0).gameObject.activeSelf)
            {
                playerObj.GetComponent<Player>().weapon = "ARROW";
                weaponButton.transform.GetChild(0).gameObject.SetActive(false);
                weaponButton.transform.GetChild(1).gameObject.SetActive(true);
                Debug.LogWarning("활로 무기 바꿈");
            }

            else
            {
                playerObj.GetComponent<Player>().weapon = "FIST";
                weaponButton.transform.GetChild(0).gameObject.SetActive(true);
                weaponButton.transform.GetChild(1).gameObject.SetActive(false);
                Debug.LogWarning("주먹으로 무기 바꿈");
            }
        }

        else
        {
            Debug.LogWarning("무기가 없습니다.");
        }
    }

}
