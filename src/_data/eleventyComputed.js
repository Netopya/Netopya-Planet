module.exports = {
  galleryImages: function(data) {
    // Only load gallery images for posts that have a gallery_id
    if (data.gallery_id && data.gallery_id > 0) {
      try {
        const galleryData = require(`./gallery_${data.gallery_id}.json`);
        return galleryData;
      } catch (error) {
        console.warn(`Gallery ${data.gallery_id} not found for post: ${data.title}`);
        return [];
      }
    }
    return [];
  }
}; 