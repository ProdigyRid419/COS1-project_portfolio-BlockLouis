#include "Crafting.h"
#include "Inventory.h"

Crafting::Crafting() {

	AddRecipe("Sap Reinforced Leather", ItemID::SapReinforcedLeather, 1, { { ItemID::TreeSap, 2 }, { ItemID::Leather, 2 } });
	AddRecipe("Sap Reinforced Vine", ItemID::SapReinforcedVine, 1, { { ItemID::TreeSap, 2 }, { ItemID::Vine, 2 } });
	AddRecipe("Silk Rope", ItemID::SilkRope, 3, { { ItemID::Vine, 2 }, { ItemID::Silk, 6 } });

	AddRecipe("Vine Gear", ItemID::VineGear, 1, { { ItemID::SapReinforcedVine, 10 }, { ItemID::Vine, 20 } });
	AddRecipe("Leather Gear", ItemID::LeatherGear, 1, { { ItemID::SapReinforcedLeather, 10 }, { ItemID::Leather, 20 }, { ItemID::Vine, 10 } });

	AddRecipe("Flint Axe", ItemID::FlintAxe, 1, { { ItemID::CrudeWood, 15 }, { ItemID::Flint, 15 } });
	AddRecipe("Stone Axe", ItemID::StoneAxe, 1, { { ItemID::FlintAxe, 1 }, { ItemID::CrudeWood, 10}, { ItemID::Stone, 10 } });
	AddRecipe("Metal Axe", ItemID::MetalAxe, 1, { { ItemID::StoneAxe, 1 }, { ItemID::Hardwood, 15 }, { ItemID::Metal, 20 } });

	AddRecipe("Flint Pickaxe", ItemID::FlintPickaxe, 1, { { ItemID::CrudeWood, 15 }, { ItemID::Flint, 15 } });
	AddRecipe("Stone Pickaxe", ItemID::StonePickaxe, 1, { { ItemID::FlintPickaxe, 1 }, { ItemID::CrudeWood, 10 }, { ItemID::Stone, 10 } });
	AddRecipe("Metal Pickaxe", ItemID::MetalPickaxe, 1, { { ItemID::StonePickaxe, 1 }, { ItemID::Hardwood, 15 }, { ItemID::Metal, 20 } });
	
	AddRecipe("Spear", ItemID::Spear, 1, { { ItemID::CrudeWood, 20 }, { ItemID::Flint, 20 } });
	AddRecipe("Bow", ItemID::Bow, 1, { { ItemID::Vine, 30 }, { ItemID::CrudeWood, 30 } });
	
	AddRecipe("Flint Arrows", ItemID::FlintArrow, 4, { { ItemID::CrudeWood, 1 }, { ItemID::Flint, 3 } });
	AddRecipe("Stone Arrows", ItemID::StoneArrow, 4, { { ItemID::CrudeWood, 1 }, { ItemID::Stone, 3 } });
	AddRecipe("Metal Arrows", ItemID::MetalArrow, 4, { { ItemID::CrudeWood, 1 }, { ItemID::Metal, 3 } });

	AddRecipe("Small Waterskin", ItemID::SmallWaterskin, 1, { { ItemID::Leather, 5 }, { ItemID::Vine, 3 } });
	AddRecipe("Medium Waterskin", ItemID::MediumWaterskin, 1, { { ItemID::SmallWaterskin, 1 }, { ItemID::Leather, 15 }, { ItemID::Vine, 8 } });
	AddRecipe("Large Waterskin", ItemID::LargeWaterskin, 1, { {ItemID::MediumWaterskin, 1 }, { ItemID::SapReinforcedLeather, 10 }, { ItemID::SapReinforcedVine, 5 } });

	AddRecipe("Basic Bandage", ItemID::BasicBandage, 3, { { ItemID::Vine, 10}, { ItemID::MedicinalHerbs, 5 } });
	AddRecipe("Improved Bandage", ItemID::ImprovedBandage, 5, { { ItemID::Leather, 10}, { ItemID::MedicinalHerbs, 10 }, { ItemID::SapReinforcedVine, 5 } });

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



