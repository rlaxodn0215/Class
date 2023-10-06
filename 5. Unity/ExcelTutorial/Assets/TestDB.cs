using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[ExcelAsset]
public class TestDB : ScriptableObject
{
	public List<TestDBEntity> 캐릭터; // Replace 'EntityType' to an actual type that is serializable.
	public List<TestDBEntity1> Spec; // Replace 'EntityType' to an actual type that is serializable.
}
