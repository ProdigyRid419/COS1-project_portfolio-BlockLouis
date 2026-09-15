#include "Crafting.h"
#include "Inventory.h"

Crafting::Crafting() {

	AddRecipe("Flint Axe", ItemID::FlintAxe, 1, { { ItemID::CrudeWood, 15 }, { ItemID::Flint, 15 } });
	AddRecipe("Flint Pickaxe", ItemID::FlintPickaxe, 1, { { ItemID::CrudeWood, 15 }, { ItemID::Flint, 15 } });
	AddRecipe("Stone Axe", ItemID::StoneAxe, 1, { { ItemID::CrudeWood, 25 }, { ItemID::Stone, 25} });
	AddRecipe("Stone Axe (UPGRADE)", ItemID::StoneAxe, 1, { { ItemID::FlintAxe, 1 }, { ItemID::CrudeWood, 10}, { ItemID::Stone, 10 } });
	AddRecipe("Stone Pickaxe", ItemID::StonePickaxe, 1, { { ItemID::CrudeWood, 25}, { ItemID::Stone, 25} });
	AddRecipe("Stone Pickaxe (UPGRADE)", ItemID::StonePickaxe, 1, { { ItemID::FlintPickaxe, 1 }, { ItemID::CrudeWood, 10 }, { ItemID::Stone, 10 } });
	AddRecipe("Metal Axe", ItemID::MetalAxe, 1, { { ItemID::Hardwood, 30 }, { ItemID::Metal, 40 } });
	AddRecipe("Metal Axe (UPGRADE)", ItemID::MetalAxe, 1, { { ItemID::StoneAxe, 1 }, { ItemID::Hardwood, 15 }, { ItemID::Metal, 20 } });
	AddRecipe("Metal Pickaxe", ItemID::MetalPickaxe, 1, { { ItemID::Hardwood, 30 }, { ItemID::Metal, 40 } });
	AddRecipe("Metal Pickaxe (UPGRADE)", ItemID::MetalPickaxe, 1, { { ItemID::StonePickaxe, 1 }, { ItemID::Hardwood, 15 }, { ItemID::Metal, 20 } });
	AddRecipe("Spear", ItemID::Spear, 1, { { ItemID::CrudeWood, 20 }, { ItemID::Flint, 20 } });
	AddRecipe("Bow", ItemID::Bow, 1, { { ItemID::Vine, 30 }, { ItemID::CrudeWood, 30 } });
	AddRecipe("Flint Arrows", ItemID::FlintArrow, 4, { { ItemID::CrudeWood, 1 }, { ItemID::Flint, 3 } });
	AddRecipe("Stone Arrows", ItemID::StoneArrow, 4, { { ItemID::CrudeWood, 1 }, { ItemID::Stone, 3 } });
	AddRecipe("Metal Arrows", ItemID::MetalArrow, 4, { { ItemID::CrudeWood, 1 }, { ItemID::Metal, 3 } });


}

bool Crafting::CanCraft(const Inventory& inventory, const CraftingRecipe& recipe) const {

	for (const RecipeIngredient& ingredient : recipe.ingredients) {

		if (inventory.GetItemCount(ingredient.ingredientType) < ingredient.requiredAmount) {

			return false;

		}

	}

	return true;

}

bool Crafting::CraftItem(Inventory& inventory, const CraftingRecipe& recipe) const {

	if (!CanCraft(inventory, recipe)) {

		return false;

	}

	Inventory tempInventory = inventory;

	for (const RecipeIngredient& ingredient : recipe.ingredients) {

		Item ingredientItem(ingredient.ingredientType);
		int remaining = tempInventory.RemoveItem(ingredientItem, ingredient.requiredAmount);
		if (remaining > 0) {

			return false;

		}

	}

	Item craftingResult(recipe.recipeResult);
	int overflow = tempInventory.AddItem(craftingResult, recipe.recipeResultAmount);
	if (overflow > 0) {

		return false;

	}

	inventory = tempInventory;
	return true;

}

const std::vector<CraftingRecipe>& Crafting::GetCraftingRecipes() const {

	return craftingRecipes;

}

void Crafting::AddRecipe(const std::string& recipeName, ItemID craftedResult, int craftedAmount, const std::vector<RecipeIngredient>& ingredientList) {

	CraftingRecipe newRecipe;
	newRecipe.recipeName = recipeName;
	newRecipe.recipeResult = craftedResult;
	newRecipe.recipeResultAmount = craftedAmount;
	newRecipe.ingredients = ingredientList;
	craftingRecipes.push_back(newRecipe);

}



