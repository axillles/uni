const fs = require('fs');
const path = require('path');

const dbPath = path.join(__dirname, 'db.json');

function readData() {
    const data = fs.readFileSync(dbPath, 'utf8');
    return JSON.parse(data);
}

function writeData(data) {
    fs.writeFileSync(dbPath, JSON.stringify(data, null, 2));
}

function getAllRecipes() {
    const data = readData();
    return data.recipes;
}

function getRecipeById(id) {
    const data = readData();
    return data.recipes.find(recipe => recipe.id === parseInt(id));
}

function createRecipe(recipe) {
    const data = readData();
    const newId = data.recipes.length > 0 ? Math.max(...data.recipes.map(r => r.id)) + 1 : 1;
    const newRecipe = { ...recipe, id: newId };
    data.recipes.push(newRecipe);
    writeData(data);
    return newRecipe;
}

function updateRecipe(id, updatedRecipe) {
    const data = readData();
    const index = data.recipes.findIndex(recipe => recipe.id === parseInt(id));
    if (index === -1) return null;
    
    data.recipes[index] = { ...updatedRecipe, id: parseInt(id) };
    writeData(data);
    return data.recipes[index];
}

function deleteRecipe(id) {
    const data = readData();
    const index = data.recipes.findIndex(recipe => recipe.id === parseInt(id));
    if (index === -1) return false;
    
    data.recipes.splice(index, 1);
    writeData(data);
    return true;
}

module.exports = {
    getAllRecipes,
    getRecipeById,
    createRecipe,
    updateRecipe,
    deleteRecipe
}; 