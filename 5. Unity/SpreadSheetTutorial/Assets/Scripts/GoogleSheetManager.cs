using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class GoogleSheetManager : MonoBehaviour
{
    const string URL = "https://docs.google.com/spreadsheets/d/1BsdOO1ZLW2VvWUC2RIG7jD0mg-K94TYvMTLKCYSmt7c/export?format=tsv&range=A2:C";
    // export?format=tsv => tsv ���� �������� ����, & range = A2:C3 => ������ ���� �� ����

    IEnumerator Start()
    {
        UnityWebRequest www = UnityWebRequest.Get(URL);
        yield return www.SendWebRequest();   // URL�� ���

        string Data = www.downloadHandler.text; // string �����ͷ� �޾ƿ�
        Debug.Log("End Receving");
        ShowText(Data);
        //CheckNameAndChange(Data);
    }


    void ShowText(string tsv)
    {
        //���� �������� ������.
        string[] row = tsv.Split('\n');
        // ���� ��
        int rowSize = row.Length;
        // ���� ��
        int columSize = row[0].Split('\t').Length;

        // ���� ���̷� ���η� ������.
        for (int i = 0; i < rowSize; i++)
        {
            string[] column = row[i].Split('\t');

            // ���� ���̷� ���η� ������.
            for (int j = 0; j < columSize; j++)
            {
                Debug.Log(column[j]);
            }
        }
    }


    // UI �ؽ�Ʈ�� ����

    //void CheckNameAndChange(string tsv)
    //{
    //    //���� �������� ������.
    //    string[] row = tsv.Split('\n');
    //    //  �� = ������ ��
    //    int rowSize = row.Length;
    //    // �� = ������ ��
    //    int columSize = row[0].Split('\t').Length;

    //    // ���� ���̷� ���η� ������.
    //    //����������
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
