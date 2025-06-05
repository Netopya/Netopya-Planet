module.exports = function(eleventyConfig) {
  // Copy static assets to match original site structure
  eleventyConfig.addPassthroughCopy("src/assets");
  
  // Copy bytety.html directly to maintain original URL structure
  eleventyConfig.addPassthroughCopy("src/bytety.html");
  
  // Map image directories from src/assets to root level paths for compatibility
  eleventyConfig.addPassthroughCopy({
    "src/assets/images/article_images": "article_images"
  });
  eleventyConfig.addPassthroughCopy({
    "src/assets/images/gallery_images": "gallery_images"
  });
  eleventyConfig.addPassthroughCopy({
    "src/assets/images/site": "images"
  });
  
  // Map code directory from src/assets to root level for article_code compatibility
  eleventyConfig.addPassthroughCopy({
    "src/assets/code": "article_code"
  });
  
  // Map other static assets from src/assets to root level paths
  eleventyConfig.addPassthroughCopy({
    "src/assets/css": "css"
  });
  eleventyConfig.addPassthroughCopy({
    "src/assets/js": "js"
  });
  
  // Copy Bootstrap 5 from node_modules
  eleventyConfig.addPassthroughCopy({
    "node_modules/bootstrap/dist/css/bootstrap.min.css": "css/bootstrap.min.css"
  });
  eleventyConfig.addPassthroughCopy({
    "node_modules/bootstrap/dist/css/bootstrap.min.css.map": "css/bootstrap.min.css.map"
  });
  eleventyConfig.addPassthroughCopy({
    "node_modules/bootstrap/dist/js/bootstrap.bundle.min.js": "js/bootstrap.bundle.min.js"
  });
  eleventyConfig.addPassthroughCopy({
    "node_modules/bootstrap/dist/js/bootstrap.bundle.min.js.map": "js/bootstrap.bundle.min.js.map"
  });

  // Watch CSS files for changes
  eleventyConfig.addWatchTarget("./src/assets/css/");
  
  // Collections
  eleventyConfig.addCollection("posts", function(collectionApi) {
    return collectionApi.getFilteredByGlob("src/posts/*.md");
  });
  
  eleventyConfig.addCollection("tutorials", function(collectionApi) {
    return collectionApi.getFilteredByGlob("src/posts/*.md").filter(item => {
      return item.data.category === 'tutorials';
    });
  });
  
  eleventyConfig.addCollection("projects", function(collectionApi) {
    return collectionApi.getFilteredByGlob("src/posts/*.md").filter(item => {
      return item.data.category === 'projects';
    });
  });
  
  eleventyConfig.addCollection("tools", function(collectionApi) {
    return collectionApi.getFilteredByGlob("src/posts/*.md").filter(item => {
      return item.data.category === 'tools';
    });
  });
  
  // Date filters
  eleventyConfig.addFilter("dateFormat", function(dateObj) {
    return new Date(dateObj).toLocaleDateString('en-US', {
      year: 'numeric',
      month: 'long',
      day: 'numeric'
    });
  });
  
  // Excerpt filter 
  eleventyConfig.addFilter("excerpt", function(content, length = 150) {
    const text = content.replace(/<[^>]*>/g, ''); // Strip HTML
    return text.length > length ? text.substring(0, length) + '...' : text;
  });
  
  return {
    dir: {
      input: "src",
      output: "_site",
      includes: "_includes",
      layouts: "_layouts",
      data: "_data"
    },
    markdownTemplateEngine: "njk",
    htmlTemplateEngine: "njk",
    templateFormats: ["html", "njk", "md"]
  };
}; 