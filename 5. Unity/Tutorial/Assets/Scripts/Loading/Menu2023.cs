using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEditor;
using UnityEditor.SceneManagement;

public class Menu2023 : MonoBehaviour
{
    [MenuItem("Menu2023/Clear PlayerPrefs")]
    private static void Clear_PlayerPrefsAll()
    {
        PlayerPrefs.DeleteAll(); // 현재 씬에 저장된 데이터 지우기
        Debug.Log("Clear_PlayerPrefsAll");
    }

    [MenuItem("Menu2023/SubMenu/Select")]
    private static void SubMenu_Select()
    {
        Debug.Log("Sub Menu 1 - Select");
    }

    // % - Ctrl
    // # - Shift
    // & - Alt
    [MenuItem("Menu2023/SubMenu/Hotkey Test 1 %#[")] //Ctrl + Shift [
    private static void SubMenu_Hotkey_1()
    {
        Debug.Log("Hotkey Test : Ctrl + Shift + [");
    }

    [MenuItem("Assets/Load Seleced Scene")]
    private static void LoadSelecedScene()
    {
        var seleced = Selection.activeObject;

        if (EditorApplication.isPlaying)
            EditorSceneManager.LoadScene(AssetDatabase.GetAssetPath(seleced));
        else
            EditorSceneManager.OpenScene(AssetDatabase.GetAssetPath(seleced));

    }

}
