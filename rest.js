const express = require('express');
const router = express.Router();
const store = require('./store');

router.get('/recipes', (req, res) => {
    const recipes = store.getAllRecipes();
    res.json(recipes);
});

router.get('/recipes/:id', (req, res) => {
    const recipe = store.getRecipeById(req.params.id);
    if (!recipe) {
        return res.status(404).json({ message: 'Рецепт не найден' });
    }
    res.json(recipe);
});

router.post('/recipes', (req, res) => {
    const recipe = store.createRecipe(req.body);
    res.status(201).json(recipe);
});

router.put('/recipes/:id', (req, res) => {
    const recipe = store.updateRecipe(req.params.id, req.body);
    if (!recipe) {
        return res.status(404).json({ message: 'Рецепт не найден' });
    }
    res.json(recipe);
});

router.delete('/recipes/:id', (req, res) => {
    const success = store.deleteRecipe(req.params.id);
    if (!success) {
        return res.status(404).json({ message: 'Рецепт не найден' });
    }
    res.status(204).send();
});

module.exports = router; 