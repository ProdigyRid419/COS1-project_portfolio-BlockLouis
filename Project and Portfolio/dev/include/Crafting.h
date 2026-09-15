#pragma once
#include "Item.h"
#include <vector>
#include <string>

class Inventory;

struct RecipeIngredient {

	ItemID ingredientType = ItemID::Empty;
	int requiredAmount = 0;

};

struct CraftingRecipe {

	std::string recipeName;
	ItemID recipeResult = ItemID::Empty;
	int recipeResultAmount = 0;
	std::vector<RecipeIngredient> ingredients;

};

class Crafting {

public:

	Crafting();
	const std::vector<CraftingRecipe>& GetCraftingRecipes() const;

	bool CanCraft(const Inventory& inventory, const CraftingRecipe& recipe) const;
	bool CraftItem(Inventory& inventory, const CraftingRecipe& recipe) const;

private:

	std::vector<CraftingRecipe> craftingRecipes;
	void AddRecipe(const std::string& recipeName, ItemID craftedResult, int craftedAmount, const std::vector<RecipeIngredient>& ingredientList);

};


