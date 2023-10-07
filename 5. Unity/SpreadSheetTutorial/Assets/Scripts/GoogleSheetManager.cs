using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class GoogleSheetManager : MonoBehaviour
{
    const string URL = "https://docs.google.com/spreadsheets/d/1BsdOO1ZLW2VvWUC2RIG7jD0mg-K94TYvMTLKCYSmt7c/export?format=tsv&range=A2:C";
    // export?format=tsv => tsv 파일 형식으로 추출, & range = A2:C3 => 가져올 엑셀 셀 범위

    IEnumerator Start()
    {
        UnityWebRequest www = UnityWebRequest.Get(URL);
        yield return www.SendWebRequest();   // URL과 통신

        string Data = www.downloadHandler.text; // string 데이터로 받아옴
        Debug.Log("End Receving");
        ShowText(Data);
        //CheckNameAndChange(Data);
    }


    void ShowText(string tsv)
    {
        //가로 기준으로 나눈다.
        string[] row = tsv.Split('\n');
        // 행의 양
        int rowSize = row.Length;
        // 열의 양
        int columSize = row[0].Split('\t').Length;

        // 행의 길이로 가로로 나눈다.
        for (int i = 0; i < rowSize; i++)
        {
            string[] column = row[i].Split('\t');

            // 열의 길이로 세로로 나눈다.
            for (int j = 0; j < columSize; j++)
            {
                Debug.Log(column[j]);
            }
        }
    }


    // UI 텍스트와 연결

    //void CheckNameAndChange(string tsv)
    //{
    //    //가로 기준으로 나눈다.
    //    string[] row = tsv.Split('\n');
    //    //  열 = 세로의 양
    //    int rowSize = row.Length;
    //    // 오 = 가로의 양
    //    int columSize = row[0].Split('\t').Length;

    //    // 열의 길이로 가로로 나눈다.
    //    //ㅁㅁㅁㅁㅁ
    //    string[] column = new string[columSize - 1];
    //    for (int i = 0; i < rowSize; i++)
    //    {
    //        column = row[i].Split('\t');

    //        Debug.Log(column[0]);

    //        for (int j = 0; j < textUIDataBase.names.Length; j++)
    //        {
    //            if (column[0] == textUIDataBase.names[j].text)
    //            {
    //                textUIDataBase.qty[j].text = column[1];
    //                textUIDataBase.price[j].text = column[2];
    //                textUIDataBase.priceUSD[j].text = column[3];
    //            }
    //        }
    //    }
    //}
}
